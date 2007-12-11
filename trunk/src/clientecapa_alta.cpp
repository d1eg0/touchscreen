#include "clientecapa_alta.h"
#include <SDL/SDL_thread.h>
#include <sstream>
#include <iostream>
#include "tabla.h"

extern SDL_mutex *mutexCapaAlta;
extern SDL_cond *caminoNuevoCond;

void ClienteCapaAlta::onConnect()
{
    //cout << this->getStatus() << endl;
    cout << "ClienteCapaAlta: conectando..." << endl;
    while(this->getStatus()==1001){}//Esperar la conexion
    extern Tabla tcampos;
    tcampos.update("CONEX","bien");
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
	Send(memblock,size);
	//Send("hola");
    }else cerr << "[E]: No se puede abrir el fichero" << endl;
}
void ClienteCapaAlta::onClose(){
    cerr << "[E]: conexion cerrada" << endl;
    extern Tabla tcampos;
    tcampos.update("CONEX","mal ");
}
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

void ClienteCapaAlta::onError(int ssError){
    switch(ssError){
	case 2004:
	    cerr << "[E]:" << ssError << " - Error de conexion" << endl;
	    break;
	case 2008:
	    cerr << "[E]:" << ssError << " - Intentas enviar sin conexión" << endl;
	    break;
	default:
	    cerr << "[E]:" << ssError << " - Error conexión indefinido" << endl;
	    break;
    }
    extern Tabla tcampos;
    tcampos.update("CONEX","mal ");
}

vector<Punto> ClienteCapaAlta::getCamino(){
    return listaPuntos;
}

void ClienteCapaAlta::clearCamino(){
    listaPuntos.clear();
}

