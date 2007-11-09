#include "campo.h"
#include "constantes.h"
#include <string>
#include <SDL/SDL_gfxPrimitives.h>

using namespace std;

Campo::Campo(SDL_Surface *surface, 
	string nombre, 
	bool estatico)
{
    this->surface=surface;
    this->nombre=nombre;
    this->estatico=estatico;
    if(!estatico){
	bmas=new Boton(surface);
	bmenos=new Boton(surface);
    }
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
    
		
    SDL_LockSurface(surface);
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
    if(!this->estatico){
	bmas->cargarBoton(	    
		areav.x+areav.w+20, 
		y, 
		20,
		20,
		"+",
		0x01F33EFF);
	bmenos->cargarBoton(	    
		areav.x+areav.w+40, 
		y, 
		20,
		20,
		"-",
		0xFF4848FF);
    }
    SDL_UnlockSurface(surface);
	//SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
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
    SDL_LockSurface(surface);
    SDL_SetClipRect(surface,  &areav);
    boxColor(
	    surface,
	    areav.x,
	    areav.y,
	    areav.x+areav.w,
	    areav.y+areav.h,
	    0x000000ff);
    stringColor(
	surface,
	areav.x, 
	(int)(areav.y+(areav.h*0.5)-(SIZE_C*0.5)), 
	valorc, 
	colorValor);
    SDL_UpdateRect(surface, 0, 0, SCREEN_W, SCREEN_H);
    SDL_UnlockSurface(surface);
    
}

void Campo::updateValor(string valor){
    this->valorstr=valor;
    this->areav.w=SIZE_C*valorstr.size();
    SDL_LockSurface(surface);
    SDL_SetClipRect(surface,  &areav);
    boxColor(
	    surface,
	    areav.x,
	    areav.y,
	    areav.x+areav.w,
	    areav.y+areav.h,
	    0x000000ff);
    stringColor(
	surface,
	areav.x, 
	(int)(areav.y+(areav.h*0.5)-(SIZE_C*0.5)), 
	valorstr.c_str(), 
	colorValor);
    SDL_UpdateRect(surface, 0, 0, SCREEN_W, SCREEN_H);
    SDL_UnlockSurface(surface);
}

void Campo::aumentar(){
    valor+=incremento;
}

void Campo::disminuir(){
    valor-=incremento;
}

int Campo::presionado(int x, int y){
    if(bmas->presionado(x,y))return 2;
    if(bmenos->presionado(x,y))return 1;
    return 0;
}
