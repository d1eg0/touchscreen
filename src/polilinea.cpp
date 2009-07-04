/**
 *       @file  polilinea.cpp
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

#include "polilinea.h"

Polilinea::Polilinea(int num, bool cerrado, string capa){
    this->numVertices=num;
    this->cerrado=cerrado;
    this->capa=capa;
    this->nombre_hab="";
}

Polilinea::~Polilinea(){
    listaVertices.clear();
}

vector<Punto>* Polilinea::getPolilinea(){
    return &listaVertices;
}

void Polilinea::addVertice(Punto vertice){
    listaVertices.push_back(vertice);
}

bool Polilinea::getCerrado(){
    return cerrado;
}

int Polilinea::getNumTotal(){
    return numVertices;
}

int Polilinea::getNum(){
    return listaVertices.size();
}

vector<Linea> Polilinea::toLineas(){
    vector<Linea> vLineas;
    vector<Punto> parVertices;
    vLineas.clear();
    vector<Punto>::iterator i_vertice;
    for(i_vertice=listaVertices.begin(); i_vertice!=listaVertices.end(); i_vertice++){
	parVertices.push_back((*i_vertice));
	if(parVertices.size()==2){
	    Punto v1(parVertices.front().getX(),parVertices.front().getY()),
		    v2(parVertices.back().getX(),parVertices.back().getY());
	    
	    Linea nuevaLinea(capa,v1.getX(),
		    v1.getY(),
		    v2.getX(),
		    v2.getY());
	    vLineas.push_back(nuevaLinea);
	    parVertices.clear();
	    parVertices.push_back(v2);
	}	
    }
    if (cerrado) {
	Linea lineaCerrar(capa,
		vLineas.front().getX1(),
		vLineas.front().getY1(),
		vLineas.back().getX2(),
		vLineas.back().getY2());
	vLineas.push_back(lineaCerrar);
    }
    
    return vLineas;
}

void Polilinea::setHabitacion(string nombre){
    this->nombre_hab=nombre;
}

string Polilinea::getHabitacion(){
    return nombre_hab;
}
