/**
 *       @file  tabla.h
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

#ifndef TABLA_H
#define TABLA_H
#include <map>
#include <utility>
#include <string>
#include "campo.h"
#include "frame.h"
#include <iostream>
#include "clientecapa_alta.h"
using namespace std;

/**
 *  \class Tabla
 *  \brief tabla compuesta por elementos de clase Campo
 *   
 *  \par 
 */
class Tabla{
public:
    Tabla();
    ~Tabla();

    /** Añadir un campo a la tabla con la etiqueta unica 'n' */
    void add(string n,Campo *c);

    /** Devuelve el campo con la etiqueta 'n' */
    Campo get(string n);

    /** Cambia el valor del campo con la etiqueta 'n' por el valor string 'v'*/
    void update(string n, string v);

    /** Cambia el valor del campo con la etiqueta 'n' por el valor float 'v'*/
    void update(string n, float v);

    /** Gestiona el input de la pantalla tactil */
    void handle(int x, int y);

    /** Recarga la tabla en el Frame 'frame' */
    void recargar(Frame *frame);

private:
    map<string, Campo> tabla;


};
#endif
