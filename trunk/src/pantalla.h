/**
 *       @file  pantalla.h
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

#ifndef PANTALLA_H
#define PANTALLA_H
#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "frame.h"
#include "punto.h"
using namespace std;

/**
 *  \class Pantalla
 *  \brief Gestiona todos los aspectos relacionados con el monitor (como la resoluci&oacute;n).
 *   
 *  \par 
 */
class Pantalla
{
public:
    /** Instancia de la pantalla */
    Pantalla(SDL_Surface *screen);

    ~Pantalla();
    /** Devuelve el puntero a la pantalla */
    SDL_Surface* getPantalla();
    /** Ocultar el cursor */
    void hideCursor();
    /** Gestiona la entrada del teclado */
    void entrada();
    /** Limpia la pantalla */
    void borrar();
    /** Oscurece la zona indicada */
    void setAlpha(Frame *frame, Uint8 zona);
    /** Devuelve si se ha salido del programa */
    bool salir();
    /** Minimiza las 3 ventanas */
    void minimizar();
    /** Desactiva el mapa */
    void mapaOff();
    /** Modifica el valor de gestionar o no la entrada */ 
    void setHandle(bool handle);
private:
    SDL_Surface* screen;
    int h_screen;
    int v_screen;
    bool sdl_quit,
	 //alpha,
	 handle,
	 pcontestada;
    const SDL_VideoInfo *info;


};
#endif

	

