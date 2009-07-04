/**
 *       @file  capa.h
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

#ifndef CAPA_H
#define CAPA_H

#include <iostream>
#include <vector>
#include "linea.h"
#include "polilinea.h"
#include "punto.h"

using namespace std;

/**
 *  \class Capa
 *  \brief La clase Mapa est&aacute; divididaa en capas
 *   
 *  \par 
 */

class Capa {
public:
    Capa();
    /** Instanciar una nueva capa con nombre 'nombre' */ 
    Capa(string nombre);
    ~Capa();
    /** Obtener las l&iacute;neas de la capa */
    vector<Linea>* getCapa();
    /** Obtener las polil&iacute;neas de la capa */
    vector<Polilinea>* getPolilinea();
    /** Añadir una l&iacute; a la capa */
    void addLinea(Linea linea);
    /** Añadir una polil&iacute; a la capa */
    void addPolilinea(Polilinea polilinea);
    /** Añadir un v&eacute;rtice a la capa */
    void addVertice(Punto vertice);
    /** Obtener el nombre de la capa */
    string getNombre();
    /** Limpiar el vector de polil&iacute;neas */
    void clear();
private:
    vector<Linea> listaLineas;
    vector<Polilinea> listaPolilineas;
    string nombre;
};
#endif

