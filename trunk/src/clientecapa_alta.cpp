#include <SolarSockets/SolarSockets++.h>
#include <fstream>
#include "clientecapa_alta.h"
#include <SDL/SDL_thread.h>
#include <sstream>
#include <iostream>
extern SDL_mutex *mutexCapaAlta;
extern SDL_cond *caminoNuevoCond;
void ClienteCapaAlta::onConnect()
{
    //caminonuevo=false;
    //cout << this->getStatus() << endl;
    if(SDL_mutexP(mutexCapaAlta)==0){
	cout << "\tE:antes" << endl;
	//Entrada sección crítica
	valor=0;
	//Salida seccion critica
	SDL_mutexV(mutexCapaAlta);
	cout << "\tS:antes" << endl;
    }
    while(this->getStatus()==1001){}//Esperar la conexion
    if(SDL_mutexP(mutexCapaAlta)==0){
	cout << "\tE:despues" << endl;
	//Entrada sección crítica
	valor=1;
	//Salida seccion critica
	SDL_mutexV(mutexCapaAlta);
	cout << "\tS:despues" << endl;
    }
    ifstream::pos_type size;
    char * memblock;
    ifstream myFile ("maps/modelo.dxf", ios::in|ios::binary|ios::ate );
    if (myFile.is_open()){
	size = myFile.tellg();
	memblock=new char[size];
	myFile.seekg (0, ios::beg);
	myFile.read (memblock, size);
	myFile.close();
	//Send(memblock,size);
	Send("hola");
    }else cerr << "Error: No se puede abrir el fichero" << endl;
}
void ClienteCapaAlta::onDataArrival(string Data)
{
    cout << "Datos:" << Data << endl;   
    listaPuntos.clear();
    string coord=Data,xstr,ystr;
    size_t pos;
    pos=coord.find_first_of(" ");
    while (pos!=string::npos)
    {	
	xstr=coord.substr(0,pos);
	coord.erase(0,pos+1);
	cout << "dato:\"" << coord << "\""<< endl;
	pos=coord.find_first_of(" ");	
	if(pos==string::npos){
	    ystr=coord;
	}else{
	    ystr=coord.substr(0,pos);	
	    coord.erase(0,pos+1);
	}
	stringstream buffer;
	double x,y;
	buffer.clear();
	buffer << xstr;
	buffer >> x;
	buffer.clear();
	buffer << ystr;
	buffer >> y;
	Punto p(x,y);
	cout << "x:"<< x << " y:" << y << endl;
	listaPuntos.push_back(p);
    }
    //Activar la condicion del thread gestor_capaalta
    SDL_CondSignal(caminoNuevoCond);
    //caminonuevo=true;
}
void ClienteCapaAlta::onDataArrival(const char* Data, unsigned int Length)
{
    cout << "hola" << endl;
}
void ClienteCapaAlta::onError(int ssError){
    if(SDL_mutexP(mutexCapaAlta)==0){
	cout << "\tE:error" << endl;
	//Entrada sección crítica
	valor=0;
	//Salida seccion critica
	SDL_mutexV(mutexCapaAlta);
	cout << "\tS:error" << endl;
    }
    cerr << ssError <<":Error de conexion" << endl;
}

/*bool ClienteCapaAlta::caminoNuevo(){
    return caminonuevo;
}*/
vector<Punto> ClienteCapaAlta::getCamino(){
//    caminonuevo=false;
    return listaPuntos;
}

float ClienteCapaAlta::getValor(){
    float valorbkp;
    if(SDL_mutexP(mutexCapaAlta)){
	cout << "\tE" << endl;
	//Entrada sección crítica
	valorbkp=this->valor;
	//Salida seccion critica
	SDL_mutexV(mutexCapaAlta);
	cout << "\tS" << endl;
    }
    return valorbkp;
}
