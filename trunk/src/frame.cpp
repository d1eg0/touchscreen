#include "frame.h"
#include "constantes.h"
#include "dibujar.h"
#include <SDL/SDL_gfxPrimitives.h>

Frame::Frame(SDL_Surface *Ventana)
{
	area.h=0;
	area.w=0;
	area.x=0;
	area.y=0;
	ventana=Ventana;
}

Frame::~Frame()
{

}

void Frame::cargarFrame(int x, int y, int w, int h, char *c, Uint32 color)
{
    Dibujar paleta(ventana);
    this->color=color;
    area.h=h;
    area.w=w;
    area.x=x;
    area.y=y;

    estado=MINIMO;

    contenedor.x=area.x;
    contenedor.y=area.y-MARGEN;
    contenedor.w=w+4;
    contenedor.h=h;
    SDL_SetClipRect(ventana, &contenedor);
    //Fondo
    SDL_FillRect(ventana, &area, color);
    //Borde
    rectangleColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, 0xFFA500FF);
    //Etiqueta
    stringColor(ventana, area.x, area.y-9, c, 0xFFA500FF);
    //Boton maximizar
    max=new Boton(ventana);
    max->cargarBoton(x+w-10,y-10,10,10,"X", 0xFFA500FF);
    SDL_SetClipRect(ventana, &contenedor);
    SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
}

void Frame::cerrarFrame(){
    SDL_SetClipRect(ventana, &contenedor);
    SDL_FillRect(ventana, &contenedor, 0x000000);
    SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
    estado=CERRADO;
}

void Frame::limpiarFrame(){
    SDL_SetClipRect(ventana, &area);
    SDL_FillRect(ventana, &area, color);
    //Borde
    rectangleColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, 0xFFA500FF);
    SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
}

SDL_Surface* Frame::getVentana(){
    return ventana;
}

bool Frame::Presionado(int x,int y)
{
	return (x>area.x)&&(x<area.x+area.w)&&
		(y>area.y)&&(y<area.y+area.h);
}


int Frame::getX(){
    return area.x;
}

int Frame::getY(){
    return area.y;
}

int Frame::getW(){
    return area.w;
}

int Frame::getH(){
    return area.h;
}

SDL_Rect Frame::getArea(){
    return area;
}

Boton* Frame::getBM(){
    return max;
}

Boton* Frame::getBm(){
    return min;
}

Uint8 Frame::cambiarEstado(){
    if(estado==MAXIMO)estado=MINIMO;
    else estado=MAXIMO;
}
