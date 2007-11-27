#include "boton.h"
#include "constantes.h"
#include <string>
#include <SDL/SDL_gfxPrimitives.h>
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

}

Boton::~Boton()
{

}

bool Boton::getEstado(){
    return estado;
}

void Boton::cargarBoton(int x, int y, int w, int h, char *c, Uint32 color)
{
	this->color=color;
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
	boxColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, color);
	rectangleColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, 0xffffffff);
	string str(c);
	stringColor(ventana,
		(int)( area.x+(area.w*0.5)-(SIZE_C*str.size()*0.5)), 
		(int)(area.y+(area.h*0.5)-(SIZE_C*0.5)), 
		c, 
		0xffffffFF);
	if(SDL_MUSTLOCK(ventana))SDL_UnlockSurface(ventana);
	SDL_UpdateRect(ventana, contenedor.x, contenedor.y, contenedor.w, contenedor.h);
	SDL_mutexV(semVideo);
	estado=activo;
}

void Boton::recargarBoton(){
    this->cargarBoton(area.x,area.y,area.w,area.h,texto,color);
}

bool Boton::presionado(int x,int y)
{
	return estado&&(x>area.x)&&(x<area.x+area.w)&&
		(y>area.y)&&(y<area.y+area.h);
}

void Boton::desactivar(){
    estado=inactivo;
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
