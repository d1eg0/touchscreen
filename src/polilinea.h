/**
 *       @file  polilinea.h
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

#ifndef POLILINEA_H
#define POLILINEA_H

#include <iostream>
#include <vector>
#include "punto.h"
#include "linea.h"
using namespace std;

/**
 *  \class Polilinea
 *  \brief Elemento formado por un conjunto de Puntos.
 *   
 *  \par 
 */

class Polilinea {
public:
    /** Instancia de una polil&iacute;nea en la capa 'capa', con 'num' v&eacute;rtices, 'cerrado' si es cerrado o abierto */
    Polilinea(int num, bool cerrado, string capa);
    ~Polilinea();

    /** Devuelve la lista de puntos de la polil&iacute;nea */
    vector<Punto>* getPolilinea();
    /** A&ntilde;adir un v&eacute; a la polil&iacute;nea */
    void addVertice(Punto vertice);
    /** Devuelve si la polil&iacute;nea es cerrada */
    bool getCerrado();
    /** Devuelve el n&uacute;mero total de v&eacute;rtices de la polil&iacute;nea */
    int getNumTotal();
    /** Devuelve el n&uacute;mero de v&eacute;rtices de la polil&iacute;nea */
    int getNum();
    /** Transforma la lista de puntos de la polil&iacute;nea en l&iacute;neas */
    vector<Linea> toLineas();
    /** Poner nombre a la polil&iacute;nea como habitaci&oacute;n */
    void setHabitacion(string nombre);
    /** Devuelve el nombre de la habitaci&oacute;n */
    string getHabitacion();
private:
    string capa;
    string nombre_hab;
    vector<Punto> listaVertices;
    bool cerrado;
    int numVertices;
};
#endif

