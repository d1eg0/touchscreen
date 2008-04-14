/**
 *    \file  capa.cpp
 *   \brief  
 *
 *  Detailed description starts here.
 *
 *  \author  Diego García Valverde , kobydiego@gmail.com
 *
 *  \internal
 *    Created:  26/09/07
 *   Compiler:  gcc/g++
 *    Company:  UIB
 *
 *  This source code is released for free distribution under the terms of the
 *  GNU General Public License as published by the Free Software Foundation.
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
