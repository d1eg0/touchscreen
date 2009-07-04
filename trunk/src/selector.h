/**
 *       @file  selector.h
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

#ifndef SELECTOR_H
#define SELECTOR_H
#include <string>
#include <vector>
#include <SDL/SDL.h>
#include "boton.h"
using namespace std;
/**
 * @class Selector
 * @brief Gestiona la selecci&oacute;n de mapas de un dispositivo USB 
 */
class Selector{


public:
    /** Constructor de la clase */
    Selector(SDL_Surface* pantalla);
    ~Selector();
    /** Obtiene un listado de ficheros del path "ruta" con extensi&oacute; "ext" */
    void buscarW(string ruta,string ext);
    void buscarR();
    /** Muestra la lista de ficheros obtenida */
    void cargar();
    /** Comprueba si la lista de ficheros est&aacute; vac&iacute;a */
    bool vacio();
    /** Comprueba que plano de la lista ha sido pulsado */
    bool handle(int x,int y);
private:
    vector<Boton> lista;
    SDL_Surface* ventana;
    string ruta;
    string ext;
    vector<string> mapas;
    int descf[2];
};
#endif
