/**
 *       @file  linea.cpp
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


#include "linea.h"
using namespace std;
Linea::Linea(string capa, double x1, double y1, double x2, double y2){
    this->capa=capa;
    this->x1=x1;
    this->y1=y1;
    this->x2=x2;
    this->y2=y2;
}

Linea::Linea(string capa, Punto v1, Punto v2){
    this->capa=capa;
    this->x1=v1.getX();
    this->y1=v1.getY();
    this->x2=v2.getX();
    this->y2=v2.getY();
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

