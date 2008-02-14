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
#include "punto.h"
/**
 *  \class Linea
 *  \brief linea del mapa asignada a una capa
 *   
 *  \par 
 */
class Linea {
public:
    /** Crear una linea en la capa 'capa', de origen (x1,y1) y destino (x2,y2) */
    Linea(string capa, double x1, double y1, double x2, double y2);
    /** Crear una linea en la capa 'capa' de origen v1 y destino v2 */
    Linea(string capa, Punto v1, Punto v2);
    ~Linea();
    /** Devuelve x1 de la linea */
    double getX1();
    /** Devuelve y1 de la linea */
    double getY1();
    /** Devuelve x2 de la linea */
    double getX2();
    /** Devuelve y2 de la linea */
    double getY2();
    /** Devuelve el nombre de la capa a la que pertenece la l&iacute;nea */
    string getCapa();
private:
    double x1,y1,x2,y2; 
    string capa;
};
#endif

