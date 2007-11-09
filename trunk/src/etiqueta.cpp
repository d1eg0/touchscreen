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
	texto="?";
	ventana=Ventana;


}

Etiqueta::~Etiqueta()
{

}


void Etiqueta::cargarEtiqueta(int x, int y, int w, int h, char *c, Uint32 colorFuente, Uint32 colorBorde, Uint32 colorRelleno)
{
	this->colorFuente=colorFuente;
	this->colorBorde=colorBorde;
	this->colorRelleno=colorRelleno;
	area.h=h;
	area.w=w;
	area.x=x;
	area.y=y;
	
	contenedor.x=x-5;
	contenedor.y=y-5;
	contenedor.w=w+10;
	contenedor.h=h+10;
	if(SDL_MUSTLOCK(ventana))SDL_LockSurface(ventana);	
	SDL_SetClipRect(ventana, &contenedor);
	boxColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, colorRelleno);
	rectangleColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, colorBorde);

	string str(c);
	stringColor(ventana,(int)( area.x+(area.w*0.5)-(SIZE_C*str.size()*0.5)), (int)(area.y+(area.h*0.5)-(SIZE_C*0.5)), c, colorFuente);
	if(SDL_MUSTLOCK(ventana))SDL_UnlockSurface(ventana);
	SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
}

void Etiqueta::insertarTexto(char *c){

    if(SDL_MUSTLOCK(ventana)) SDL_LockSurface(ventana);	
    SDL_SetClipRect(ventana, &contenedor);
    boxColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, colorRelleno);
    rectangleColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, colorBorde);

    string str(c);
    stringColor(ventana,(int)( area.x+(area.w*0.5)-(SIZE_C*str.size()*0.5)), (int)(area.y+(area.h*0.5)-(SIZE_C*0.5)), c, colorFuente);

    if(SDL_MUSTLOCK(ventana)) SDL_UnlockSurface(ventana);
    SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
}
