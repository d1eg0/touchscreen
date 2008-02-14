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
using namespace std;

/**
 *  \class Dibujar
 *  \brief Generar el plano
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

