#include "clientecapa_baja.h"
#include <SDL/SDL.h>
#include "tabla.h"
#include "silla.h"
#include "constantes.h"
extern SDL_cond* sensorNuevoCond;
extern SDL_mutex* mutexCapaBaja;

void ClienteCapaBaja::onConnect()
{
    //cout << this->getStatus() << endl;
    while(this->getStatus()==1001){SDL_Delay(1);}//Esperar la conexion
    extern Frame *framestado;
    if(framestado->getEstado()!=CERRADO){
	extern Tabla tcampos;
	tcampos.update("CONEX","bien");
    }
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

    if(Data.find(string(CABECERA_ERROR))==string::npos){
	double x,y;
	char *pblanco;
	x=strtod(Data.c_str(),&pblanco);
	y=strtod(pblanco,&pblanco);

	if(Data.find(string(CABECERA_POS))!=string::npos){
	    Data.erase(0,(string(CABECERA_POS)).size());
	    x=strtod(Data.c_str(),&pblanco);
	    y=strtod(pblanco,&pblanco);
	    angulo=strtod(pblanco,&pblanco);
	    Punto p(x,y);
	    SDL_mutexP(mutexCapaBaja);
	    pos=p;
	    extern Silla *silla;
	    silla->setPos(p);
	    silla->dibujar();
	    SDL_mutexV(mutexCapaBaja);
	}else if(Data.find(string(CABECERA_SENS))!=string::npos){
	    Data.erase(0,(string(CABECERA_SENS)).size());
	    int i;
	    float val;
	    pblanco=(char *)Data.c_str();
	    for (i=0;i<4;i++){
		val=strtod(pblanco,&pblanco);
		sensor[i]=val;
		cout << "valor" << i << ":" << val;
	    }
	}

	/*if(Data.find(CABECERA_FINRUTA)!=string::npos){
	    SDL_CondSignal(caminoNuevoCond);
	}*/
    }//else SDL_CondSignal(caminoNuevoCond);
    
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
    extern Tabla tcampos;
    tcampos.update("CONEX","mal ");
}

vector<double> ClienteCapaBaja::getValores(){
    return listaValores;
}


