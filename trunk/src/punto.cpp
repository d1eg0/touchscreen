/**
 *       @file  punto.cpp
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

#include "punto.h"

using namespace std;

Punto::Punto(){
}
Punto::Punto(double x, double y){
    //this->capa=capa;
    this->x=x;
    this->y=y;
}

Punto::~Punto(){
}


double Punto::getX(){
    return x;
}
double Punto::getY(){
    return y;
}

void Punto::cpantalla(Frame *frame, double dh, double dv,double escala){
    double factor=escala/100.0;
    this->y*=factor;
    this->x*=factor;
    this->y= (frame->getH()+frame->getY())-this->y-dv;//negativo porque el eje Y+ apunta a Y-
    this->x= frame->getX()+this->x+dh;

}

void Punto::cplano(double x, double y, Frame *frame, double dh, double dv, double escala){
    double factor=100.0/escala;
    this->x=x-frame->getX()-dh;
    this->y=(frame->getH()+frame->getY())-dv-y;
    this->x*=factor;
    this->y*=factor;
    //this->x=(x-ox)*factor;
    //this->y=(-y+oy)*factor;
    cout << "Xplano: " << this->x << endl;
    cout << "Yplano: " << this->y << endl;
}
/*string Punto::getCapa(){
    return capa;
}*/

/*void Punto::escalar(double escala){
    if (escala>500||escala<0)
	cerr<<"Error: escala incorrecta"<<endl;
    else{
	double factor=100.0/escala;
	this->x1/=factor;
	this->y1/=factor;
	this->x2/=factor;
	this->y2/=factor;
    }

}*/
