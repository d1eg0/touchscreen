/**
 *       @file  dxfparser.cpp
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

#include "dxfparser.h"
#include <iostream>
#include <stdlib.h>
#include "mapa.h"
#include "linea.h"
#include "capa.h"
#include "polilinea.h"
#include "punto.h"
using namespace std;
extern Mapa plano;
DxfParser::DxfParser(){}

void DxfParser::addLine(const DL_LineData& data) {
    Linea nuevalinea(attributes.getLayer().c_str(),data.x1,data.y1,data.x2,data.y2);
    
    plano.getCapa(nuevalinea.getCapa())->addLinea(nuevalinea);
}

void DxfParser::addLayer(const DL_LayerData& data) {
    Capa nuevacapa(data.name);
    plano.addCapa(nuevacapa);
}

void DxfParser::addPolyline(const DL_PolylineData& data) {
    bool cerrado;
    if(data.flags==1)cerrado=true;
    else cerrado=false;
    Polilinea nuevapolilinea(data.number,cerrado,attributes.getLayer().c_str());
    if(attributes.getLayer()=="CapaHabitacions"){
	nuevapolilinea.setHabitacion(nombre);
    }
    plano.getCapa(attributes.getLayer().c_str())->addPolilinea(nuevapolilinea);
}

void DxfParser::addVertex(const DL_VertexData& data) {

    Punto nuevoPunto(data.x,data.y);
    string capa=attributes.getLayer().c_str();
    plano.getCapa(capa)->addVertice(nuevoPunto);
    if (plano.getCapa(capa)->getPolilinea()->back().getNumTotal()==
	    plano.getCapa(capa)->getPolilinea()->back().getNum())
    {
	vector<Linea> vPolilineas;
	vPolilineas=plano.getCapa(capa)->getPolilinea()->back().toLineas();
	 
	vector<Linea>::iterator i_linea;
	for(i_linea=vPolilineas.begin(); i_linea!=vPolilineas.end(); i_linea++){
	    plano.getCapa(capa)->addLinea((*i_linea));
	}
    }
}

void DxfParser::addBlock(const DL_BlockData& data){
    if(data.name[0]!='*')
	nombre=data.name.c_str();
}

	
