/**
 *       @file  clientecapa_alta.cpp
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

#include "clientecapa_alta.h"
#include <SDL/SDL_thread.h>
#include <sstream>
#include <iostream>
#include "tabla.h"
#include "constantes.h"


extern SDL_mutex *mutexCapaAlta;
extern SDL_cond *caminoNuevoCond;
void ClienteCapaAlta::setMap(string path){
    this->path=path;
}

int conectarAlta(void *data){
    ClienteCapaAlta *cli=(ClienteCapaAlta*)data;
    while(cli->getStatus()!=1002){
	cli->Connect("192.168.1.5", 9999);
	SDL_Delay(1000);
	cout << "estado:" <<cli->getStatus() << endl;
    }
    cout << "Conectado:" <<cli->getStatus() << endl;
    return 0;
}
void ClienteCapaAlta::conectar(){
    SDL_CreateThread(conectarAlta, (void*)this);
}

void ClienteCapaAlta::onConnect()
{
    //cout << this->getStatus() << endl;
    cout << "ClienteCapaAlta: conectando..." << endl;
    while(this->getStatus()==1001){cout << "Espero servidor..." << endl;SDL_Delay(1000);}//Esperar la conexion
    extern Frame *framestado;
    if(framestado->getEstado()!=CERRADO){
	extern Tabla tcampos;
	tcampos.update("CONEX","bien");
    }
    cout << "ClienteCapaAlta: conectado!" << endl;
    enviarPlano(path);
}
void ClienteCapaAlta::onClose(){
    cerr << "[E]: conexion cerrada" << endl;
    extern Tabla tcampos;
    tcampos.update("CONEX","mal ");
    this->conectar();
}
void ClienteCapaAlta::onLineArrival(string Cadena)
{
    cout << "\t****ClienteCapaAlta recibe:\"" << Cadena <<"\"" << endl;   
    cout << "Rx-Bytes:" << getNumBytesReceived() << " Bloques:" << getNumBlocksReceived() <<endl;
    string Data(Cadena);
    if(Data.find(string(CABECERA_ERROR))==string::npos){
	double x,y;
	char *pblanco;
	if((Data.find(string(CABECERA_INIRUTA))!=string::npos)&&
		(Data.find(string(CABECERA_FINRUTA))==string::npos)){
	    modo=CABECERA_INIRUTA;
	    Data.erase(0,7);
	    x=strtod(Data.c_str(),&pblanco);
	    y=strtod(pblanco,&pblanco);
	    cout << "Pto("<< x << ","<< y << ")\n" << endl;
	}else if(Data.find(string(CABECERA_FINRUTA))!=string::npos){
	    SDL_CondSignal(caminoNuevoCond);
	    modo=CABECERA_FINRUTA;
	}else if(Data.find(string(CABECERA_STATUS))!=string::npos){
	    modo=CABECERA_STATUS;
	}

	if(modo==CABECERA_INIRUTA){
	    Punto p(x,y);
	    cout << "x:"<< x << " y:" << y << endl;
	    SDL_mutexP(mutexCapaAlta);
	    listaPuntos.push_back(p);
	    SDL_mutexV(mutexCapaAlta);
	}else if(modo==CABECERA_STATUS){
	    Data.erase(0,7);
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
    }else cerr << "[E]: No se puede abrir el fichero" << endl;
}

void ClienteCapaAlta::enviar(string dato){
    Send(dato+"\r\n");
}



