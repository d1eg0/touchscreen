/**
 *       @file  campo.cpp
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

#include "campo.h"
#include "constantes.h"
#include <sstream>
#include <iostream>
#include <SDL/SDL_gfxPrimitives.h>

using namespace std;
Campo::Campo(SDL_Surface *surface, 
	string nombre, 
	bool estatico,
	Uint32 colorNombre, 
	Uint32 colorValor)
{
    this->surface=surface;
    this->nombre=nombre;
    this->estatico=estatico;
    if(!estatico){
	bmas=new Boton(surface);
	bmenos=new Boton(surface);
	bok=new Boton(surface);
    }
    this->colorNombre=colorNombre;
    this->colorValor=colorValor;
    this->modificado=false;
}

Campo::~Campo()
{

}

void Campo::cargarCampo(int x, int y, Uint32 colorNombre, Uint32 colorValor)
{
    this->colorNombre=colorNombre;
    this->colorValor=colorValor;
    this->arean.x=x;
    this->arean.y=y;
    this->arean.w=SIZE_C*nombre.size();
    this->arean.h=SIZE_C*2;
		
    extern SDL_mutex *semVideo;
    SDL_mutexP(semVideo);
    if(SDL_MUSTLOCK(surface))SDL_LockSurface(surface);
    SDL_SetClipRect(surface,  &arean);

    stringColor(
	    surface,
	   (int)( arean.x+(arean.w*0.5)-(SIZE_C*nombre.size()*0.5)), 
	    (int)(arean.y+(arean.h*0.5)-(SIZE_C*0.5)), 
	    nombre.c_str(), 
	    colorNombre);
    
    if (numerico){
	char *valorc=(char *)malloc(sizeof(float));
	sprintf(valorc,"%5.3f",this->valor);
	this->areav.x=x+arean.w;
	this->areav.y=y;
	this->areav.w=SIZE_C*string(valorc).size();
	this->areav.h=SIZE_C*2;
	SDL_SetClipRect(surface,  &areav);
	stringColor(
		surface,
		areav.x, 
		(int)(areav.y+(areav.h*0.5)-(SIZE_C*0.5)), 
		valorc, 
		colorValor);
    }else{
	this->areav.x=x+arean.w;
	this->areav.y=y;
	this->areav.w=SIZE_C*valorstr.size();
	this->areav.h=SIZE_C*2;
	SDL_SetClipRect(surface,  &areav);
	stringColor(
		surface,
		areav.x, 
		(int)(areav.y+(areav.h*0.5)-(SIZE_C*0.5)), 
		valorstr.c_str(), 
		colorValor);
    }
    if(SDL_MUSTLOCK(surface))SDL_UnlockSurface(surface);
    SDL_mutexV(semVideo);
    if(!this->estatico){
	bmas->cargarBoton(	    
		arean.x+120, 
		y-5, 
		20,
		20,
		"+",
		0x01F33EFF,
		COLOR_BORDER_BOTON);
	bmenos->cargarBoton(	    
		arean.x+140, 
		y-5, 
		20,
		20,
		"-",
		0xFF4848FF,
		COLOR_BORDER_BOTON);
	bok->cargarBoton(	    
		arean.x+160, 
		y-5, 
		30,
		20,
		"ok",
		0x20B2AAFF,
		COLOR_BORDER_BOTON);

	if(modificado==false){
	    bok->desactivar();
	    bok->borrar();
	}

    }
	//SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
}

void Campo::recargar(){
    cargarCampo(arean.x,arean.y,colorNombre,colorValor);
    SDL_UpdateRect(surface, areav.x, areav.y, areav.w, areav.h);
    SDL_UpdateRect(surface, arean.x, arean.y, arean.w, arean.h);
}

void Campo::recargar(int x, int y){
    cargarCampo(x,y,colorNombre,colorValor);
    SDL_UpdateRect(surface, areav.x, areav.y, areav.w, areav.h);
    SDL_UpdateRect(surface, arean.x, arean.y, arean.w, arean.h);
}
void Campo::valorStr(string valor){
    this->valorstr=valor;
    this->numerico=false;
    this->estatico=true;
}

void Campo::valorNum(float valor, float vmax, float vmin, float incremento){
    this->valor=valor;
    this->maxvalor=vmax;
    this->minvalor=vmin;
    this->incremento=incremento;
    this->numerico=true;
}

void Campo::updateValor(float valor){
    this->valor=valor;
   char *valorc=(char *)malloc(sizeof(float));
    sprintf(valorc,"%5.3f",this->valor);
    this->areav.w=SIZE_C*string(valorc).size();
    extern SDL_mutex *semVideo;
    SDL_mutexP(semVideo);
    if(SDL_MUSTLOCK(surface))SDL_LockSurface(surface);
    SDL_SetClipRect(surface,  &areav);
    boxColor(
	    surface,
	    areav.x,
	    areav.y,
	    areav.x+areav.w,
	    areav.y+areav.h,
	    0xffffffff);
    stringColor(
	surface,
	areav.x, 
	(int)(areav.y+(areav.h*0.5)-(SIZE_C*0.5)), 
	valorc, 
	colorValor);
    if(SDL_MUSTLOCK(surface))SDL_UnlockSurface(surface);
    SDL_UpdateRect(surface, areav.x, areav.y, areav.w, areav.h);
    SDL_mutexV(semVideo);
    
}

void Campo::updateValor(string valor){
    this->valorstr=valor;
    this->areav.w=SIZE_C*valorstr.size();
    extern SDL_mutex *semVideo;
    SDL_mutexP(semVideo);
    if(SDL_MUSTLOCK(surface))SDL_LockSurface(surface);
    SDL_SetClipRect(surface,  &areav);
    boxColor(
	    surface,
	    areav.x,
	    areav.y,
	    areav.x+areav.w,
	    areav.y+areav.h,
	    0xffffffff);
    Uint32 cv;
    if(valor.find("mal")==string::npos){
	cv=colorValor;
    }else cv=0xff0000ff;
    stringColor(
	surface,
	areav.x, 
	(int)(areav.y+(areav.h*0.5)-(SIZE_C*0.5)), 
	valorstr.c_str(), 
	cv);
    if(SDL_MUSTLOCK(surface))SDL_UnlockSurface(surface);
    SDL_UpdateRect(surface, areav.x, areav.y, areav.w, areav.h);
    SDL_mutexV(semVideo);
}

void Campo::aumentar(){
    valor+=incremento;
    updateValor(valor);
}

void Campo::disminuir(){
    valor-=incremento;
    updateValor(valor);
}


string Campo::getVstr(){
    if (!numerico)
	return valorstr;
    else{
	string v;
	stringstream buffer;
	buffer << valor;
	buffer >> v;
	return v;
    }
}

int Campo::presionado(int x, int y){
    if(bmas->presionado(x,y))return 2;
    if(bmenos->presionado(x,y))return 1;
    if(bok->presionado(x,y))return 3;
    return 0;
}

/** Se encarga del input mouse 
 *  Retorna true si se ha presionado Ok
 *  retorna false en cualquier otro caso
 * */
bool Campo::handle(int x, int y){
    if(!estatico){
	switch ( this->presionado( x, y)){
	case 0:
	    return false;
	    break;
	case 1:
	    if((valor-incremento)>minvalor){
		modificado=true;
		bok->recargarBoton();
		disminuir();
	    }
	    return false;
	    break;
	case 2:
	    if((valor+incremento)<maxvalor){
		modificado=true;
		bok->recargarBoton();
		aumentar();
	    }
	    return false;
	    break; 
	case 3:
	    modificado=false;
	    bok->desactivar();
	    bok->borrar();
	    return true;
	    break;
	}
    }
    return false;
}
