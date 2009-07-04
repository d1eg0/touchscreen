/**
 *       @file  frame.cpp
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

#include "frame.h"
#include "constantes.h"
#include "dibujar.h"
#include "etiqueta.h"
#include <SDL/SDL_gfxPrimitives.h>

Frame::Frame(SDL_Surface *ventana)
{
    area.h=0;
    area.w=0;
    area.x=0;
    area.y=0;

    areamax.h=0;
    areamax.w=0;
    areamax.x=0;
    areamax.y=0;
    this->ventana=ventana;
    this->estado=CERRADO;
    bmaxmin=new Boton(ventana);
}

Frame::~Frame()
{

}

void Frame::cargarFrame(int x, int y, int w, int h, string c, Uint32 color)
{
    extern SDL_mutex *semVideo;
    //Cordenadas de los campos
    xc=x+5;
    yc=y+5;

    //Dibujar paleta(ventana);
    this->color=color;

    this->area.h=h;
    this->area.w=w;
    this->area.x=x;
    this->area.y=y;

    /*this->areamax.h=SCREEN_H-MARGEN;
      this->areamax.w=SCREEN_W-2*MARGEN;
      this->areamax.x=x;
      this->areamax.y=y;*/
    this->titulo=c;
    this->estado=MINIMO;

    this->contenedor.x=x;
    this->contenedor.y=y-MARGENV;
    this->contenedor.w=w+4;
    this->contenedor.h=h;

    /*    this->contenedormax.x=areamax.x;
	  this->contenedormax.y=areamax.y-MARGEN;
	  this->contenedormax.w=SCREEN_W-MARGEN;
	  this->contenedormax.h=SCREEN_H-MARGEN;
	  */  
    this->limpiarFrame(true);
    //Etiqueta
    Etiqueta etitulo(ventana);
    etitulo.cargarEtiqueta(
	    area.x,
	    area.y-15,
	    titulo.size()*SIZE_C,
	    SIZE_C*2,
	    (char *)titulo.c_str(),
	    COLOR_FUENTE,
	    0,
	    COLOR_BG);

    //Boton maximizar
    //bcerrar=new Boton(ventana);
    //bcerrar->cargarBoton(x+w-15,y-T_BOTON,T_BOTON,T_BOTON,"X", 0xFFA500FF);
    //bmaxmin=new Boton(ventana);
    bmaxmin->cargarBoton(x+w-2*T_BOTON,y-T_BOTON,T_BOTON*2,T_BOTON,"+", 0xFFA500FF, COLOR_BORDER_BOTON);
    bmaxmin->setIcono("img/bmax.bmp");
    //SDL_SetClipRect(ventana, &area);
    //SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
}


void Frame::maxFrame(int x,int y,int w,int h){
    estado=MAXIMO;
    this->areamax.h=h;
    this->areamax.w=w;
    this->areamax.x=x;
    this->areamax.y=y;

    this->contenedormax.x=areamax.x;
    this->contenedormax.y=areamax.y-MARGENV;
    this->contenedormax.w=w;
    this->contenedormax.h=h+MARGENH;

    this->limpiarFrame(true);
    //Etiqueta
    Etiqueta etitulo(ventana);
    etitulo.cargarEtiqueta(
	    areamax.x,
	    areamax.y-15,
	    string(titulo).size()*SIZE_C,
	    SIZE_C*2,
	    (char*)titulo.c_str(),
	    COLOR_FUENTE,
	    0,
	    COLOR_BG);	
    //Boton maximizar
    //bcerrar=new Boton(ventana);
    //bcerrar->cargarBoton(areamax.x+areamax.w-15,areamax.y-T_BOTON,T_BOTON,T_BOTON,"X", 0xFFA500FF);
    //bmaxmin=new Boton(ventana);
    bmaxmin->cargarBoton(areamax.x+areamax.w-2*T_BOTON,areamax.y-T_BOTON,2*T_BOTON,T_BOTON,"-", 0xFFA500FF, COLOR_BORDER_BOTON);
    bmaxmin->setIcono("img/bmin.bmp");
    //SDL_SetClipRect(ventana, &areamax);
    //SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
    xc=x+5;
}

void Frame::minFrame(){
    estado=MINIMO;
    this->limpiarFrame(true);
    //Etiqueta
    Etiqueta etitulo(ventana);
    etitulo.cargarEtiqueta(
	    area.x,
	    area.y-15,
	    string(titulo).size()*SIZE_C,
	    SIZE_C*2,
	    (char*)titulo.c_str(),
	    COLOR_FUENTE,
	    0,
	    COLOR_BG);	
    //Boton maximizar
    //bcerrar=new Boton(ventana);
    //bcerrar->cargarBoton(area.x+area.w-15,area.y-T_BOTON,T_BOTON,T_BOTON,"X", 0xFFA500FF);
    //Boton maximizar
    //bmaxmin=new Boton(ventana);
    bmaxmin->cargarBoton(
	    area.x+area.w-2*T_BOTON,
	    area.y-T_BOTON,
	    2*T_BOTON,
	    T_BOTON,
	    "+", 
	    0xFFA500FF,
	    COLOR_BORDER_BOTON);
    bmaxmin->setIcono("img/bmax.bmp");
    //SDL_SetClipRect(ventana, &area);
    //SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
    xc=getX()+5;
}

void Frame::desactivarFrame(){
    bmaxmin->desactivar();
    estado=CERRADO;
}

void Frame::limpiarFrame(bool refresh){
    SDL_Rect a=this->getArea();
    extern SDL_mutex *semVideo;
    SDL_mutexP(semVideo);
    if(SDL_MUSTLOCK(ventana))SDL_LockSurface(ventana);
    SDL_SetClipRect(ventana, &a);
    SDL_FillRect(ventana, &a, color);
    //Borde
    rectangleColor(ventana, a.x, a.y, a.x+a.w-1, a.y+a.h-1, COLOR_BORDER_FRAME);
    if(SDL_MUSTLOCK(ventana))SDL_UnlockSurface(ventana);
    if (refresh)
	SDL_UpdateRect(ventana, a.x, a.y, a.w, a.h);
    SDL_mutexV(semVideo);
    //bmaxmin->desactivar();
}

void Frame::activarFrame(){
    SDL_Rect a=this->getArea();
    extern SDL_mutex *semVideo;
    SDL_mutexP(semVideo);
    SDL_SetClipRect(ventana, &a);
    SDL_mutexV(semVideo);
}

void Frame::refrescarFrame(){
    SDL_Rect a=this->getArea();
    extern SDL_mutex *semVideo;
    SDL_mutexP(semVideo);
    SDL_UpdateRect(ventana, a.x, a.y, a.w, a.h);
    SDL_mutexV(semVideo);
}

SDL_Surface* Frame::getVentana(){
    return ventana;
}

bool Frame::presionado(int x,int y)
{
//    cout << "dentro" << endl;
    return (x>this->getX())&&(x<(this->getX()+this->getW()))&&
	(y>this->getY())&&(y<(this->getY()+this->getH()));
}


int Frame::getX(){
    if(estado==MINIMO)return area.x;
    else if(estado==MAXIMO)return areamax.x;
}

int Frame::getY(){
    if(estado==MINIMO)return area.y;
    else if(estado==MAXIMO)return areamax.y;
}

int Frame::getW(){
    if(estado==MINIMO)return area.w;
    else if(estado==MAXIMO)return areamax.w;
}

int Frame::getH(){
    if(estado==MINIMO)return area.h;
    else if(estado==MAXIMO)return areamax.h;
}

SDL_Rect Frame::getArea(){
    if(estado==MINIMO)return area;
    else if(estado==MAXIMO)return areamax;
}

/*Boton* Frame::getBcerrar(){
  return bcerrar;
  }*/

Boton* Frame::getBmaxmin(){
    return bmaxmin;
}

Uint8 Frame::getEstado(){
    return estado;
}


