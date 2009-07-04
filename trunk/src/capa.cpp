/**
 *       @file  capa.cpp
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


#include "capa.h"

Capa::Capa(){
}
Capa::Capa(string nombre){
    this->nombre=nombre;
}

Capa::~Capa(){
    listaLineas.clear();
}

vector<Linea>* Capa::getCapa(){
    return &listaLineas;
}

vector<Polilinea>* Capa::getPolilinea(){
    return &listaPolilineas;
}

void Capa::addLinea(Linea linea){
    listaLineas.push_back(linea);
}

void Capa::addPolilinea(Polilinea polilinea){
    listaPolilineas.push_back(polilinea);
}

void Capa::addVertice(Punto punto){
    listaPolilineas.back().addVertice(punto);
}


string Capa::getNombre(){
    return nombre;
}

void Capa::clear(){
    listaPolilineas.clear();
}
