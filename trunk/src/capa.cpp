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

Capa::Capa(string nombre,int color){
    this->nombre=nombre;
    this->color=color;
}

Capa::~Capa(){
    listaLineas.clear();
}

vector<Linea>* Capa::getCapa(){
    return &listaLineas;
}

void Capa::addLinea(Linea linea){
    listaLineas.push_back(linea);
}


int Capa::getColor(){
    return color;
}

string Capa::getNombre(){
    return nombre;
}

