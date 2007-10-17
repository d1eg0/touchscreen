/**
 *    \file  Campo.cpp
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

#include "Campo.h"

Campo::Campo(string nombre,int color){
    this->nombre=nombre;
    this->color=color;
}

Campo::~Campo(){
    listaLineas.clear();
}

vector<Linea>* Campo::getCampo(){
    return &listaLineas;
}

vector<Polilinea>* Campo::getPolilinea(){
    return &listaPolilineas;
}

void Campo::addLinea(Linea linea){
    listaLineas.push_back(linea);
}

void Campo::addPolilinea(Polilinea polilinea){
    listaPolilineas.push_back(polilinea);
}

void Campo::addVertice(Vertice vertice){
    listaPolilineas.back().addVertice(vertice);
}

int Campo::getColor(){
    return color;
}

string Campo::getNombre(){
    return nombre;
}

void Campo::clear(){
    listaPolilineas.clear();
}
