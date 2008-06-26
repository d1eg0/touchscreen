#include "clientecapa_alta.h"
#include <SDL/SDL_thread.h>
#include <sstream>
#include <iostream>
#include "tabla.h"
#include "constantes.h"


extern SDL_mutex *mutexCapaAlta;
extern SDL_cond *caminoNuevoCond;

void ClienteCapaAlta::onConnect()
{
    //cout << this->getStatus() << endl;
    cout << "ClienteCapaAlta: conectando..." << endl;
    while(this->getStatus()==1001){SDL_Delay(1);}//Esperar la conexion
    extern Frame *framestado;
    if(framestado->getEstado()!=CERRADO){
	extern Tabla tcampos;
	tcampos.update("CONEX","bien");
    }
    cout << "ClienteCapaAlta: conectado!" << endl;
    enviarPlano("maps/modelo.dxf");
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

    if(Data.find(CABECERA_ERROR)==string::npos){
	double x,y;
	char *pblanco;
	if(Data.find(CABECERA_INIRUTA)!=string::npos){
	    modo=CABECERA_INIRUTA;
	    Data.erase(0,6);
	    x=strtod(Data.c_str(),&pblanco);
	    y=strtod(pblanco,&pblanco);
	}else if(Data.find(CABECERA_FINRUTA)!=string::npos){
	    SDL_CondSignal(caminoNuevoCond);
	}else if(Data.find(CABECERA_STATUS)!=string::npos){
	    modo=CABECERA_STATUS;
	}

	if(modo==CABECERA_INIRUTA){
	    Punto p(x,y);
	    //cout << "x:"<< x << " y:" << y << endl;
	    SDL_mutexP(mutexCapaAlta);
	    listaPuntos.push_back(p);
	    SDL_mutexV(mutexCapaAlta);
	}else if(modo==CABECERA_STATUS){
	    Data.erase(0,(string(CABECERA_STATUS)).size());
	    double val=strtod(Data.c_str(),&pblanco);
	    status=val; 
	}

    }else SDL_CondSignal(caminoNuevoCond);
    
    //Activar la condicion del thread gestor_capaalta
}

void ClienteCapaAlta::onError(int ssError){
    switch(ssError){
	case 2004:
	    cerr << "[E]:" << ssError << " Alta - Error de conexion" << endl;
	    break;
	case 2008:
	    cerr << "[E]:" << ssError << " Alta - Intentas enviar sin conexión" << endl;
	    break;
	default:
	    cerr << "[E]:" << ssError << " Alta - Error conexión indefinido" << endl;
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
void ClienteCapaAlta::enviarPlano(string path){
    ifstream::pos_type size;
    char * memblock;
    ifstream myFile (path.c_str(), ios::in|ios::binary|ios::ate );
    if (myFile.is_open()){
	size = myFile.tellg();
	memblock=new char[size];
	myFile.seekg (0, ios::beg);
	myFile.read (memblock, size);
	myFile.close();
	Send(string(CABECERA_MAPA)+"\r\n");
	Send(memblock,size);
	//cout << memblock << endl;
    }else cerr << "[E]: No se puede abrir el fichero" << endl;
}

void ClienteCapaAlta::enviar(string dato){
    Send(dato+"\r\n");
}



