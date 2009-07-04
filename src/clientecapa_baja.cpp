/**
 *       @file  clientecapa_baja.cpp
 *
 *     @author  Diego García , kobydiego@gmail.com
 *
 *   @internal
 *     Company  Universitat de les Illes Balears
 *   Copyright  Copyright (c) 2009, Diego García
 *
 *
 *  This file is part of TouchScreenGUI.
 *  TouchScreenGUI is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  TouchScreenGUI is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TouchScreenGUI; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  http://www.gnu.org/copyleft/gpl.html
 *
 * =====================================================================================
 */

#include "clientecapa_baja.h"
#include <SDL/SDL.h>
#include "tabla.h"
#include "silla.h"
#include "constantes.h"
extern SDL_cond* sensorNuevoCond;
extern SDL_mutex* mutexCapaBaja;

int conectarBaja(void *data){
    ClienteCapaBaja *cli=(ClienteCapaBaja*)data;
    while(cli->getStatus()!=1002){
	cli->Connect("192.168.1.5", 9998);
	SDL_Delay(1000);
	cout << "estado:" <<cli->getStatus() << endl;
    }
    cout << "Conectado:" <<cli->getStatus() << endl;
    return 0;
}
void ClienteCapaBaja::conectar(){
    SDL_CreateThread(conectarBaja, (void*)this);
}


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
	    Data.erase(0,7);
	    x=strtod(Data.c_str(),&pblanco);
	    y=strtod(pblanco,&pblanco);
	    angulo=strtod(pblanco,&pblanco);
	    cout << "x: " << x << " y: " << y << " angulo: " << angulo << endl;
	    Punto p(x,y);
	    SDL_mutexP(mutexCapaBaja);
	    pos=p;
	    extern Silla *silla;
	    silla->setPos(p);
	    silla->dibujar();
	    SDL_mutexV(mutexCapaBaja);
	}else if(Data.find(string(CABECERA_SENS))!=string::npos){
	    Data.erase(0,7);
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
    this->conectar();
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


