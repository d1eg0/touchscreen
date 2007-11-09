#include "clientecapa_alta.h"
#include <SDL/SDL_thread.h>
#include <sstream>
#include <iostream>

extern SDL_mutex *mutexCapaAlta;
extern SDL_cond *caminoNuevoCond;

void ClienteCapaAlta::onConnect()
{
    //cout << this->getStatus() << endl;
    cout << "ClienteCapaAlta: conectando..." << endl;
    while(this->getStatus()==1001){}//Esperar la conexion
    cout << "ClienteCapaAlta: conectado!" << endl;
    ifstream::pos_type size;
    char * memblock;
    ifstream myFile ("maps/modelo.dxf", ios::in|ios::binary|ios::ate );
    if (myFile.is_open()){
	size = myFile.tellg();
	memblock=new char[size];
	myFile.seekg (0, ios::beg);
	myFile.read (memblock, size);
	myFile.close();
//	Send(memblock,size);
	cout << "Tx-Bytes:" << getNumBytesSent() << " Bloques:" << getNumBlocksSent() <<endl;
	//Send("hola");
    }else cerr << "Error: No se puede abrir el fichero" << endl;
}
//void ClienteCapaAlta::onDataArrival(const char* Cadena, unsigned int Length)
void ClienteCapaAlta::onLineArrival(string Cadena)
{
    cout << "\t****ClienteCapaAlta recibe:\"" << Cadena <<"\"" << endl;   
    cout << "Rx-Bytes:" << getNumBytesReceived() << " Bloques:" << getNumBlocksReceived() <<endl;
    string Data(Cadena);
    //buffer << Data <<" ";
    if(Data.find("ERROR")==string::npos){
	double x,y;
	char *pblanco;
	//Data=buffer.str();
	x=strtod(Data.c_str(),&pblanco);
	y=strtod(pblanco,&pblanco);
	Punto p(x,y);
	cout << "x:"<< x << " y:" << y << endl;
	SDL_mutexP(mutexCapaAlta);
	listaPuntos.push_back(p);
	SDL_mutexV(mutexCapaAlta);
	//si hay un dolar es final de datos
	if(Data.find("$")!=string::npos){
	    SDL_CondSignal(caminoNuevoCond);
	}
    }else SDL_CondSignal(caminoNuevoCond);
    
    //Activar la condicion del thread gestor_capaalta
}
/*void ClienteCapaAlta::onDataArrival(const char* Data, unsigned int Length)
{
    cout << "\t***Binario" << endl;
    //cout << "data:" << Data << endl;
}*/

void ClienteCapaAlta::onError(int ssError){
    cerr << ssError <<":Error de conexion" << endl;
}

vector<Punto> ClienteCapaAlta::getCamino(){
    return listaPuntos;
}

void ClienteCapaAlta::clearCamino(){
    listaPuntos.clear();
}

