/**
 *    \file  linea.h
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
#ifndef LINEA_H
#define LINEA_H

#include <dxflib/dl_dxf.h>

/**
 *  \class Linea
 *  \brief linea del mapa asignada a una capa
 *   
 *  \par 
 */
class Linea {
public:
    Linea(string capa, double x1, double y1, double x2, double y2);
    ~Linea();
    double getX1();
    double getY1();
    double getX2();
    double getY2();
    string getCapa();
    void escalar(int escala);
private:
    double x1,y1,x2,y2; 
    string capa;
};
#endif

