#include "campo.h"
#include "constantes.h"
#include <string>
#include <SDL/SDL_gfxPrimitives.h>

using namespace std;

Campo::Campo(Frame *frame, 
	string nombre, 
	bool estatico)
{
    this->frame=frame;
    this->nombre=nombre;
    this->estatico=estatico;
    if(!estatico){
	bmas=new Boton(frame->getVentana());
	bmenos=new Boton(frame->getVentana());
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
    
		
    SDL_SetClipRect(frame->getVentana(),  &arean);

    stringColor(
	    frame->getVentana(),
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
	SDL_SetClipRect(frame->getVentana(),  &areav);
	stringColor(
		frame->getVentana(),
		areav.x, 
		(int)(areav.y+(areav.h*0.5)-(SIZE_C*0.5)), 
		valorc, 
		colorValor);
    }else{
	this->areav.x=x+arean.w;
	this->areav.y=y;
	this->areav.w=SIZE_C*valorstr.size();
	this->areav.h=SIZE_C*2;
	SDL_SetClipRect(frame->getVentana(),  &areav);
	stringColor(
		frame->getVentana(),
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
    SDL_SetClipRect(frame->getVentana(),  &areav);
    boxColor(
	    frame->getVentana(),
	    areav.x,
	    areav.y,
	    areav.x+areav.w,
	    areav.y+areav.h,
	    0x000000ff);
    stringColor(
	frame->getVentana(),
	areav.x, 
	(int)(areav.y+(areav.h*0.5)-(SIZE_C*0.5)), 
	valorc, 
	colorValor);
    SDL_UpdateRect(frame->getVentana(), 0, 0, SCREEN_W, SCREEN_H);
}

void Campo::updateValor(string valor){
    this->valorstr=valor;
    this->areav.w=SIZE_C*valorstr.size();
    SDL_SetClipRect(frame->getVentana(),  &areav);
    boxColor(
	    frame->getVentana(),
	    areav.x,
	    areav.y,
	    areav.x+areav.w,
	    areav.y+areav.h,
	    0x000000ff);
    stringColor(
	frame->getVentana(),
	areav.x, 
	(int)(areav.y+(areav.h*0.5)-(SIZE_C*0.5)), 
	valorstr.c_str(), 
	colorValor);
    SDL_UpdateRect(frame->getVentana(), 0, 0, SCREEN_W, SCREEN_H);
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
