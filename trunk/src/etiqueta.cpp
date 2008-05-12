#include "etiqueta.h"
#include "constantes.h"
#include <string>
#include <SDL/SDL_gfxPrimitives.h>

using namespace std;

Etiqueta::Etiqueta(SDL_Surface *Ventana)
{
	area.h=20;
	area.w=40;
	area.x=0;
	area.y=0;
	//texto="?";
	ventana=Ventana;


}

Etiqueta::~Etiqueta()
{

}


void Etiqueta::cargarEtiqueta(int x, int y, int w, int h, string c, Uint32 colorFuente, Uint32 colorBorde, Uint32 colorRelleno)
{
	this->colorFuente=colorFuente;
	this->colorBorde=colorBorde;
	this->colorRelleno=colorRelleno|0x000000ff;
	area.h=h;
	area.w=w;
	area.x=x;
	area.y=y;
	
	contenedor.x=x-5;
	contenedor.y=y-5;
	contenedor.w=w+10;
	contenedor.h=h+10;
	extern SDL_mutex *semVideo;
	SDL_mutexP(semVideo);
	if(SDL_MUSTLOCK(ventana))SDL_LockSurface(ventana);	
	SDL_SetClipRect(ventana, &contenedor);
	boxColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, colorRelleno);
	rectangleColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, colorBorde);

	
	stringColor(ventana,(int)( area.x+(area.w*0.5)-(SIZE_C*c.size()*0.5)), (int)(area.y+(area.h*0.5)-(SIZE_C*0.5)), (char*)c.c_str(), colorFuente);
	if(SDL_MUSTLOCK(ventana))SDL_UnlockSurface(ventana);
	SDL_UpdateRect(ventana, area.x, area.y, area.w, area.h);
	SDL_mutexV(semVideo);
}

void Etiqueta::insertarTexto(string c){

    extern SDL_mutex *semVideo;
    SDL_mutexP(semVideo);
    SDL_SetClipRect(ventana, &contenedor);
    if(SDL_MUSTLOCK(ventana)) SDL_LockSurface(ventana);	
    boxColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, colorRelleno);
    rectangleColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, colorBorde);

    stringColor(ventana,(int)( area.x+(area.w*0.5)-(SIZE_C*c.size()*0.5)), (int)(area.y+(area.h*0.5)-(SIZE_C*0.5)), (char*)c.c_str(), colorFuente);

    if(SDL_MUSTLOCK(ventana)) SDL_UnlockSurface(ventana);
    SDL_UpdateRect(ventana, area.x, area.y, area.w, area.h);
    SDL_mutexV(semVideo);
}
