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
/*void Dibujar::transformar(Frame *frame, double &x, double &y,double dh, double dv,double escala){
    y= (frame->getH()+frame->getY())-y+dv;
    x= frame->getX()+x+dh;

}*/
void Dibujar::dibujarLinea(Frame *frame, Linea *linea) {
    /*double y1= (frame->getH()+frame->getY())-linea->getY1()+dv;
    double y2= (frame->getH()+frame->getY())-linea->getY2()+dv;
    double x1= frame->getX()+linea->getX1()+dh;
    double x2= frame->getX()+linea->getX2()+dh;*/
    double x1,x2,y1,y2;
    x1=linea->getX1();
    x2=linea->getX2();
    y1=linea->getY1();
    y2=linea->getY2();
    //transformar(frame,x1,y1,dh,dv,escala);
    //transformar(frame,x2,y2,dh,dv,escala);
    lineColor(screen, (Sint16)x1, (Sint16)y1, (Sint16)x2, (Sint16)y2, 0x000000ff);
}

