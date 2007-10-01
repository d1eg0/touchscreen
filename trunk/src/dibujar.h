/**
 *    \file  dibujar.h
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
#ifndef DIBUJAR_H
#define DIBUJAR_H

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "linea.h"
#include "frame.h"

/**
 *  \class Dibujar
 *  \brief Generar un plano
 *   
 *  \par 
 */

class Dibujar {

public:
    Dibujar(SDL_Surface *screen);
    ~Dibujar();
    
    void dibujarLinea(Frame *frame, Linea *linea, double dh, double dv);
private:
    SDL_Surface *screen;

};
#endif

