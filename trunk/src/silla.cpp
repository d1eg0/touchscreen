/**
 *       @file  silla.cpp
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

#include "silla.h"

Silla::Silla(Frame *frame, Mapa *plano){
    this->frame=frame;
    this->plano=plano;
    radio=1;
    rot=0;
    status=0;
}

Silla::~Silla(){
}

Punto Silla::getPos(){
    return pos;
}

void Silla::setPos(Punto pos){
    this->pos=pos;
}

int Silla::getRot(){
    extern SDL_mutex *mutexRot;
    SDL_mutexP(mutexRot);
    rot++;
    rot%=360;
    int rotacion=rot;
    SDL_mutexV(mutexRot);
    return rotacion;
}

void Silla::setRot(int r){
    extern SDL_mutex *mutexRot;
    SDL_mutexP(mutexRot);
    rot+=r;
    SDL_mutexV(mutexRot);
}
int Silla::getStatus(){
    return status;
}
void Silla::toogleStatus(){
    if (status==0) status=1;
    else status=0;
}

void Silla::dibujar(){
    int tradio;
    SDL_Rect r=frame->getArea();
    extern SDL_mutex *semVideo;
    plano->pintarMapa(frame->getVentana(),plano->getEscala());
    SDL_mutexP(semVideo);
    if(SDL_MUSTLOCK(frame->getVentana()))SDL_LockSurface(frame->getVentana());
    SDL_SetClipRect(frame->getVentana(),&r);
    tradio=(int)(radio*(plano->getEscala()/100.0)); 
    Uint32 color;
    color=0x0000ffff;
    
   
    Punto o=pos;
    o.cpantalla(frame,plano->getDH(),plano->getDV(),plano->getEscala());
    filledCircleColor(frame->getVentana(), (int)o.getX(), (int)o.getY(), tradio, color);
    filledCircleColor(frame->getVentana(), (int)o.getX(), (int)o.getY(), tradio-2, 0xffffffff);
    filledCircleColor(frame->getVentana(), (int)o.getX(), (int)o.getY(), tradio-4, color);
    filledCircleColor(frame->getVentana(), (int)o.getX(), (int)o.getY(), tradio-6, 0xffffffff);
    if(SDL_MUSTLOCK(frame->getVentana()))SDL_UnlockSurface(frame->getVentana());
//    SDL_UpdateRect(frame->getVentana(),(int)o.getX()-tradio,(int)o.getY()-tradio,tradio*3,tradio*2);
    SDL_mutexV(semVideo);
    frame->refrescarFrame();

}
