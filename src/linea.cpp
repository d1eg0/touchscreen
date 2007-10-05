/**
 *    \file  linea.cpp
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

#include "linea.h"
using namespace std;
Linea::Linea(string capa, double x1, double y1, double x2, double y2){
    this->capa=capa;
    this->x1=x1;
    this->y1=y1;
    this->x2=x2;
    this->y2=y2;
}

Linea::~Linea(){
}


double Linea::getX1(){
    return x1;
}
double Linea::getY1(){
    return y1;
}
double Linea::getX2(){
    return x2;
}
double Linea::getY2(){
    return y2;
}

string Linea::getCapa(){
    return capa;
}

void Linea::escalar(double escala){
    if (escala>500||escala<0)
	cerr<<"Error: escala incorrecta"<<endl;
    else{
	double factor=100.0/escala;
	this->x1/=factor;
	this->y1/=factor;
	this->x2/=factor;
	this->y2/=factor;
    }

}
