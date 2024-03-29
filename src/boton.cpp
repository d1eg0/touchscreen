/**
 *       @file  boton.cpp
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

#include "boton.h"
#include "constantes.h"
#include <string>
#include <SDL/SDL_gfxPrimitives.h>
#include <iostream>
#include <SDL/SDL_rotozoom.h>
using namespace std;

Boton::Boton(SDL_Surface *Ventana)
{
    area.h=20;
    area.w=40;
    area.x=0;
    area.y=0;
    texto="?";
    ventana=Ventana;
    Sizef=16;

    estado=inactivo;
    conicono=false;

}

Boton::~Boton()
{

}
string Boton::getTexto(){
    return texto;
}
bool Boton::getEstado(){
    return estado;
}

void Boton::cargarBoton(int x, int y, int w, int h, string c, Uint32 colorFondo, Uint32 colorBorde)
{
	this->colorFondo=colorFondo;
	this->colorBorde=colorBorde;
	texto=c;
	area.h=h;
	area.w=w;
	area.x=x;
	area.y=y;

	contenedor.x=area.x;
	contenedor.y=area.y;
	contenedor.w=w;
	contenedor.h=h;

	extern SDL_mutex *semVideo;
	SDL_mutexP(semVideo);
	SDL_SetClipRect(ventana, &area);
	if(SDL_MUSTLOCK(ventana))SDL_LockSurface(ventana);
	boxColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, colorFondo);
	rectangleColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, colorBorde);
	stringColor(ventana,
		(int)( area.x+(area.w*0.5)-(SIZE_C*c.size()*0.5)), 
		(int)(area.y+(area.h*0.5)-(SIZE_C*0.5)), 
		(char*)c.c_str(), 
		0xffffffFF);
	if(SDL_MUSTLOCK(ventana))SDL_UnlockSurface(ventana);
	SDL_UpdateRect(ventana, contenedor.x, contenedor.y, contenedor.w, contenedor.h);
	SDL_mutexV(semVideo);
	estado=activo;
	if(conicono==true){
	    this->setIcono(this->iconopath);
	}
}

void Boton::recargarBoton(){
    if(conicono==true){
	this->setIcono(this->iconopath);
    }else{
	this->cargarBoton(area.x,area.y,area.w,area.h,texto,colorFondo,colorBorde);
    }
}

bool Boton::presionado(int x,int y)
{
	return estado&&(x>area.x)&&(x<area.x+area.w)&&
		(y>area.y)&&(y<area.y+area.h);
}

void Boton::desactivar(){
    estado=inactivo;
}
void Boton::deshabilitar(){
    this->desactivar();
    extern SDL_mutex *semVideo;
    SDL_mutexP(semVideo);
    SDL_SetClipRect(ventana, &area);
    if(SDL_MUSTLOCK(ventana))SDL_LockSurface(ventana);
    boxColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1,0xc0c0c0aa);
    /*string str(c);
    stringColor(ventana,
	    (int)( area.x+(area.w*0.5)-(SIZE_C*str.size()*0.5)), 
	    (int)(area.y+(area.h*0.5)-(SIZE_C*0.5)), 
	    c, 
	    0xffffffFF);*/
    if(SDL_MUSTLOCK(ventana))SDL_UnlockSurface(ventana);
    SDL_UpdateRect(ventana, contenedor.x, contenedor.y, contenedor.w, contenedor.h);
    SDL_mutexV(semVideo);
}
void Boton::borrar(){
    extern SDL_mutex *semVideo;
    SDL_mutexP(semVideo);
    SDL_SetClipRect(ventana, &area);
    if(SDL_MUSTLOCK(ventana))SDL_LockSurface(ventana);
    boxColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, 0xffffffff);
    //rectangleColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, 0xffffffff);
    if(SDL_MUSTLOCK(ventana))SDL_UnlockSurface(ventana);
    SDL_UpdateRect(ventana, contenedor.x, contenedor.y, contenedor.w, contenedor.h);
    SDL_mutexV(semVideo);
    estado=activo;

}

void Boton::setIcono(string iconoruta){
  //  cout << string(iconoruta).length() <<endl;

    //iconopath=(char*)malloc((string(iconoruta).length()+100)*sizeof(char));
    //strcpy(iconopath,iconoruta);
    iconopath=iconoruta;
    this->conicono=true;
    extern SDL_mutex *semVideo;
    
    SDL_Rect offset; 
    offset.x=area.x;
    offset.y=area.y;

    SDL_Surface *iconotemp=SDL_LoadBMP((char*)iconoruta.c_str()); 
    icono=SDL_DisplayFormat(iconotemp);
    icono=rotozoomSurface (icono, 0, 1, 1);
    Uint32 colorkey = SDL_MapRGB( icono->format, 0x00, 0x00, 0x00 );
    SDL_SetColorKey( icono, SDL_SRCCOLORKEY, colorkey );
    SDL_FreeSurface( iconotemp );
    
    SDL_mutexP(semVideo);
    SDL_SetClipRect(ventana, &area);
    if(SDL_MUSTLOCK(ventana))SDL_LockSurface(ventana);
    
    SDL_BlitSurface( icono, NULL, ventana, &offset );
   
    if(SDL_MUSTLOCK(ventana))SDL_UnlockSurface(ventana);
    SDL_UpdateRect(ventana, contenedor.x, contenedor.y, contenedor.w, contenedor.h);
    SDL_mutexV(semVideo);
    estado=activo;
}

