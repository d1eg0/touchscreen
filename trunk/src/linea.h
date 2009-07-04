/**
 *       @file  linea.h
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

