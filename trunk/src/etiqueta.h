/**
 *       @file  etiqueta.h
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

#ifndef ETIQUETA_H
#define ETIQUETA_H
#include <SDL/SDL.h>
#include <iostream>


using namespace std;

/**
 *  \class Etiqueta
 *  \brief Gestiona etiquetas de texto.
 *   
 *  \par 
 */
class Etiqueta  
{
public:
    /** Especificar la "Ventana" donde se situa **/
    Etiqueta(SDL_Surface *Ventana);
    virtual ~Etiqueta();
    /** Carga la etiqueta en la posicion 'x,y' con una anchura 'w' y una altura 'h'. El texto 'c' **/ 
    void cargarEtiqueta(int x, int y, int w, int h, string c, Uint32 colorFuente, Uint32 colorBorde, Uint32 colorRelleno);
    /** Dibuja la etiqueta con la configuraci&oacute;n inicial **/ 
    void dibujarEtiqueta();
    /** Inserta el texto 'c' en la etiqueta **/ 
    void insertarTexto(string c);


     

private:
    SDL_Rect area;
    SDL_Rect contenedor;
    SDL_Surface *ventana;

    //string texto;
    Uint32 colorBorde;
    Uint32 colorFuente;
    Uint32 colorRelleno;
	

};

#endif
