/**
 *       @file  tabla.cpp
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

#include "tabla.h"
#include "constantes.h"
Tabla::Tabla(){
}
Tabla::~Tabla(){
}

void Tabla::add(string n, Campo *c){
    tabla.insert(pair<string,Campo>(n,*c));
   
}

Campo Tabla::get(string n){
    return tabla.find(n)->second;
}

void Tabla::update(string n, string v){
    tabla.find(n)->second.updateValor(v);
}

void Tabla::update(string n, float v){
    stringstream buffer;
    buffer << v;

    tabla.find(n)->second.updateValor(v);
}

void Tabla::handle(int x,int y){
    map<string, Campo>::iterator it;
    for (it=tabla.begin();it!=tabla.end();it++){
	if((*it).second.handle(x,y)){
	    extern ClienteCapaAlta clienteCapaAlta;
	    clienteCapaAlta.Send((*it).first+(*it).second.getVstr()+"\r\n");
	    cout << "envio:" << (*it).first+(*it).second.getVstr()+"\r\n" <<  endl;
	    break;
	}
    }
}

void Tabla::recargar(Frame *frame){
    int x=frame->getX();
    int y=frame->getY();
    map<string, Campo>::iterator it;
    bool columna=false;;
    for (it=tabla.begin();it!=tabla.end();it++){
	(*it).second.recargar(x+5,y+5);
	y+=20;
	if(y>(frame->getY()+frame->getH()-20)){
	    if(frame->getEstado()==MAXIMO){
		if(!columna){
		    x+=300;
		    y=frame->getY();
		    columna=true;
		}
	    }else{
		break;
	    }
	}
    }
}
