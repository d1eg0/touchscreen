/**
 *       @file  dibujar.h
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

#ifndef DIBUJAR_H
#define DIBUJAR_H

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "linea.h"
#include "frame.h"
using namespace std;

/**
 *  \class Dibujar
 *  \brief Representaci&oacute;n gr&aacute;fica del Mapa.
 *   
 *  \par 
 */

class Dibujar {

public:
    /** Instancia para dibujar en 'screen' */
    Dibujar(SDL_Surface *screen);
    ~Dibujar();
    /** Dibujar una linea 'linea' de color 'color en el frame 'frame' */
    void dibujarLinea(Frame *frame, Linea *linea, Uint32 color);
private:
    SDL_Surface *screen;

};
#endif

