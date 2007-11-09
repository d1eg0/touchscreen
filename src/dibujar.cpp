/**
 *    \file  dibujar.cpp
 *   \brief  
 *
 *  Detailed description starts here.
 *
 *  \author  Diego García Valverde , kobydiego@gmail.com
 *
 *  \internal
 *    Created:  28/09/07
 *   Compiler:  gcc/g++
 *    Company:  UIB
 *
 *  This source code is released for free distribution under the terms of the
 *  GNU General Public License as published by the Free Software Foundation.
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
    if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
    lineColor(screen, (Sint16)x1, (Sint16)y1, (Sint16)x2, (Sint16)y2, color);
    if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
    SDL_mutexV(semVideo);
}

