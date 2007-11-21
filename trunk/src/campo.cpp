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
    }
    this->colorNombre=colorNombre;
    this->colorValor=colorValor;
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
		y, 
		20,
		20,
		"+",
		0x01F33EFF);
	bmenos->cargarBoton(	    
		arean.x+140, 
		y, 
		20,
		20,
		"-",
		0xFF4848FF);
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
    return 0;
}

bool Campo::handle(int x, int y){
    if(!estatico){
	switch ( this->presionado( x, y)){
	case 1:
	    if((valor-incremento)>minvalor){
		disminuir();
		return true;
	    }else return false;
	    break;
	case 2:
	    if((valor+incremento)<maxvalor){
		aumentar();
		return true;
	    }else return false;
	    break; 
	case 0:
	    return false;
	    break;
	}
    }
    return false;
}
