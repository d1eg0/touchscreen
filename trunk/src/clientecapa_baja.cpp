#include "clientecapa_baja.h"
#include <SDL/SDL.h>
#include "tabla.h"

extern SDL_cond* sensorNuevoCond;
extern SDL_mutex* mutexCapaBaja;

void ClienteCapaBaja::onConnect()
{
    //cout << this->getStatus() << endl;
    while(this->getStatus()==1001){SDL_Delay(1);}//Esperar la conexion
    extern Tabla tcampos;
    tcampos.update("CONEX","bien");
    cout << "ClienteCapaBaja: conectado!" << endl;
    //Send("hola");

}
/*
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
*/
void ClienteCapaBaja::onLineArrival(string Cadena)
{
    cout << "\t****ClienteCapaBaja recibe:\"" << Cadena <<"\"" << endl;   
    cout << "Rx-Bytes:" << getNumBytesReceived() << " Bloques:" << getNumBlocksReceived() <<endl;
    string Data(Cadena);

    if(Data.find("ERROR")==string::npos){
	double x,y;
	char *pblanco;
	x=strtod(Data.c_str(),&pblanco);
	y=strtod(pblanco,&pblanco);
	//Punto p(x,y);
	cout << "x:"<< x << " y:" << y << endl;
	SDL_mutexP(mutexCapaBaja);
	//listaValores.push_back(p);
	SDL_mutexV(mutexCapaBaja);
	//si hay un dolar es final de datos
	if(Data.find("$")!=string::npos){
	    SDL_CondSignal(sensorNuevoCond);
	}
    }else SDL_CondSignal(sensorNuevoCond);
    
    //Activar la condicion del thread gestor_capaalta
}

void ClienteCapaBaja::onClose(){
    cerr << "[E]: conexion cerrada" << endl;
    extern Tabla tcampos;
    tcampos.update("CONEX","mal ");
}

void ClienteCapaBaja::onError(int ssError){
    switch(ssError){
	case 2004:
	    cerr << "[E]:" << ssError << " Baja - Error de conexion" << endl;
	    break;
	case 2008:
	    cerr << "[E]:" << ssError << " Baja - Intentas enviar sin conexión" << endl;
	    break;
	default:
	    cerr << "[E]:" << ssError << " Baja - Error conexión indefinido" << endl;
	    break;
    }
}

vector<double> ClienteCapaBaja::getValores(){
    return listaValores;
}


