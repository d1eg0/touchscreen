/**
 *       @file  dibujar.cpp
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

#include "dibujar.h"
#include "constantes.h"
Dibujar::Dibujar(SDL_Surface *screen){
    this->screen=screen;
}

Dibujar::~Dibujar(){
}

void Dibujar::dibujarLinea(Frame *frame, Linea *linea, Uint32 color) {
    double x1,x2,y1,y2;
    extern SDL_mutex *semVideo;
    x1=linea->getX1();
    x2=linea->getX2();
    y1=linea->getY1();
    y2=linea->getY2();
    SDL_mutexP(semVideo);
    frame->activarFrame();
    /*cout << "x1:" << x1
	<< " y1:" << y1
	<< " x2:" << x2
	<< " y2:" << x2
	<< endl;*/
    if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
    lineColor(screen, (Sint16)x1, (Sint16)y1, (Sint16)x2, (Sint16)y2, color);
    if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
    SDL_mutexV(semVideo);
}

