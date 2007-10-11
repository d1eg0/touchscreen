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
//void SetClip(SDL_Surface *screen, int x1, int y1, int x2, int y2);
void Dibujar::dibujarLinea(Frame *frame, Linea *linea, double dh, double dv) {
    double y1= (frame->getH()+frame->getY())-linea->getY1()+dv;
    double y2= (frame->getH()+frame->getY())-linea->getY2()+dv;
    double x1= frame->getX()+linea->getX1()+dh;
    double x2= frame->getX()+linea->getX2()+dh;
    lineColor(screen, (Sint16)x1, (Sint16)y1, (Sint16)x2, (Sint16)y2, 0x000000ff);
//    printf ("pintando linea... \t (%lf,%lf) (%lf,%lf)\n",x1,y1,x2,y2); 
    
}
/*void SetClip (SDL_Surface *screen, int x1, int y1, int x2, int y2)
 {
    SDL_Rect clip;
    clip.x = x1+BORDER;
    clip.y = y1+BORDER;
    clip.w = x2-x1-2*BORDER;
    clip.h = y2-y1-2*BORDER;
    SDL_SetClipRect(screen, &clip);
 }*/

