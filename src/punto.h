/**
 *       @file  punto.h
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

#ifndef PUNTO_H
#define PUNTO_H

#include <dxflib/dl_dxf.h>
#include "frame.h"
//#include "mapa.h"
/**
 *  \class Punto
 *  \brief Punto de coordenadas (x,y)
 *   
 *  \par 
 */
class Punto {
public:
    /** Instancia de un punto */
    Punto();
    /** Instancia de un punto (x,y) */
    Punto(double x, double y);
    ~Punto();
    /** Devuelve la componente X del punto */
    double getX();
    /** Devuelve la componente Y del punto */
    double getY();
    /** Cambiar sistema cordenadas de plano a  pantalla */
    void cpantalla(Frame *frame, double dh, double dv,double escala);
    // Cambiar sistema cordenadas de pantalla a plano */
    //void cplano(double x, double y, double escala, Frame *frame);
    /** Cambiar sistema cordenadas de pantalla a plano */
void cplano(double x, double y, Frame *frame, double dh, double dv, double escala);

private:
    double x,y; 
    //string capa;
};
#endif

