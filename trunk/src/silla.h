/**
 *       @file  silla.h
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

#ifndef SILLA_H
#define SILLA_H
#include "punto.h"
#include "frame.h"
#include "mapa.h"

/**
 *  \class Silla
 *  \brief Gestiona la posici&oacute;n y orientaci&oacute;n de la silla.
 *   
 *  \par 
 */
class Silla{
private:
    Punto pos;
    int radio;
    int rot;
    int status;
    Frame *frame;
    Mapa *plano;
public:
    /** Crear una silla en el Frame 'frame' en el Mapa 'plano' */
    Silla(Frame *frame, Mapa *plano);
    ~Silla();
    
    /** Devuelve la posicion de la silla */
    Punto getPos();

    /** Actualiza la posicion actual al punto 'pos' */
    void setPos(Punto pos);

    /** Devuelve la rotacion 0-360 */
    int getRot();

    /** Actualiza la rotacion actual a 'r' */
    void setRot(int r);
    /** Cambia el estado de la silla (0=apagado 1=encendido) */
    void toogleStatus();
    /** Obtiene el estado de la silla (0=apagado 1=encendido) */
    int getStatus();

    /** Dibuja la silla en la posicion correspondiente */
    void dibujar();

};
#endif
