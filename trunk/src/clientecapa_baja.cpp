#include "clientecapa_baja.h"

extern SDL_cond* sensorNuevoCond;
extern SDL_mutex* mutexCapaBaja;

void ClienteCapaBaja::onConnect()
{
    //cout << this->getStatus() << endl;
    while(this->getStatus()==1001){}//Esperar la conexion
    //Send("hola");

}
void ClienteCapaBaja::onDataArrival(string Data)
{
    cout << "ClienteCapaBaja recibe:" << Data << endl;   
    SDL_mutexP(mutexCapaBaja);//Entrada seccion critica
    listaValores.clear();
    string valores=Data,vstr;
    stringstream buffer;
    double valor;
    size_t pos;
    pos=valores.find_first_of(" ");
    while (pos!=string::npos)
    {	
	vstr=valores.substr(0,pos);
	valores.erase(0,pos+1);
	cout << "dato:\"" << valores << "\""<< endl;
	pos=valores.find_first_of(" ");	
	buffer.clear();
	buffer << vstr;
	buffer >> valor;
	cout << "v:"<< valor << endl; 
	listaValores.push_back(valor);
    }
    vstr=valores;
    buffer.clear();
    buffer << vstr;
    buffer >> valor;
    cout << "v:"<< valor << endl; 
    listaValores.push_back(valor);

    //Activar la condicion del thread gestor_capabaja
    SDL_mutexV(mutexCapaBaja);//Salida seccion critica
    SDL_CondSignal(sensorNuevoCond);
 
}
void ClienteCapaBaja::onError(int ssError){
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
}

vector<double> ClienteCapaBaja::getValores(){
    return listaValores;
}


