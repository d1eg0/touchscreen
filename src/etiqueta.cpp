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
	
	contenedor.x=x;
	contenedor.y=y;
	contenedor.w=w;
	contenedor.h=h;
		
	SDL_SetClipRect(ventana, &area);
	boxColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, colorRelleno);
	string str(c);
	printf( "++++++++++tamaño:%d\n", str.size());

	stringColor(ventana,(int)( area.x+(area.w*0.5)-(SIZE_C*str.size()*0.5)), (int)(area.y+(area.h*0.5)-(SIZE_C*0.5)), c, colorFuente);
	SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
}


