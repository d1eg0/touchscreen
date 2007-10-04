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

	areamax.h=0;
	areamax.w=0;
	areamax.x=0;
	areamax.y=0;
	ventana=Ventana;
}

Frame::~Frame()
{

}

void Frame::cargarFrame(int x, int y, int w, int h, char *c, Uint32 color)
{
    //Dibujar paleta(ventana);
    this->color=color;

    this->area.h=h;
    this->area.w=w;
    this->area.x=x;
    this->area.y=y;

    this->areamax.h=SCREEN_H-MARGEN;
    this->areamax.w=SCREEN_W-2*MARGEN;
    this->areamax.x=x;
    this->areamax.y=y;
    this->titulo=c;
    //strcpy(this->titulo,c);
    this->estado=MINIMO;

    this->contenedor.x=area.x;
    this->contenedor.y=area.y-MARGEN;
    this->contenedor.w=w+4;
    this->contenedor.h=h;

    this->contenedormax.x=area.x;
    this->contenedormax.y=area.y-MARGEN;
    this->contenedormax.w=SCREEN_W-MARGEN;
    this->contenedormax.h=SCREEN_H-4*MARGEN;
    
    SDL_SetClipRect(ventana, &contenedor);
    //Fondo
    SDL_FillRect(ventana, &area, color);
    //Borde
    rectangleColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, 0xFFA500FF);
    //Etiqueta
    stringColor(ventana, area.x, area.y-9, c, 0xFFA500FF);
    //Boton maximizar
    bcerrar=new Boton(ventana);
    bcerrar->cargarBoton(x+w-15,y-12,12,12,"X", 0xFFA500FF);
    bmaxmin=new Boton(ventana);
    bmaxmin->cargarBoton(x+w-30,y-12,12,12,"[]", 0xFFA500FF);
    SDL_SetClipRect(ventana, &contenedor);
    SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
}

void Frame::cerrarFrame(){
    SDL_SetClipRect(ventana, &contenedor);
    SDL_FillRect(ventana, &contenedor, 0x000000);
    SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
    estado=CERRADO;
}

void Frame::maxFrame(){
    estado=MAXIMO;
    SDL_SetClipRect(ventana, &contenedormax);
    //Fondo
    SDL_FillRect(ventana, &areamax, color);
    //Borde
    rectangleColor(ventana, areamax.x, areamax.y, areamax.x+areamax.w-1, areamax.y+areamax.h-1, 0xFFA500FF);
    //Etiqueta
    stringColor(ventana, areamax.x, areamax.y-9, titulo, 0xFFA500FF);
    //Boton maximizar
    bcerrar=new Boton(ventana);
    bcerrar->cargarBoton(areamax.x+areamax.w-15,areamax.y-12,12,12,"X", 0xFFA500FF);
    bmaxmin=new Boton(ventana);
    bmaxmin->cargarBoton(areamax.x+areamax.w-30,areamax.y-12,12,12,"[]", 0xFFA500FF);
    SDL_SetClipRect(ventana, &contenedormax);
    SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
}

void Frame::minFrame(){
    estado=MINIMO;
    SDL_SetClipRect(ventana, &contenedor);
    //Fondo
    SDL_FillRect(ventana, &area, color);
    //Borde
    rectangleColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, 0xFFA500FF);
    //Etiqueta
    stringColor(ventana, area.x, area.y-9, titulo, 0xFFA500FF);
    //Boton maximizar
    bcerrar=new Boton(ventana);
    bcerrar->cargarBoton(area.x+area.w-15,area.y-12,12,12,"X", 0xFFA500FF);
    bmaxmin=new Boton(ventana);
    bmaxmin->cargarBoton(area.x+area.w-30,area.y-12,12,12,"[]", 0xFFA500FF);
    SDL_SetClipRect(ventana, &contenedor);
    SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
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
    if(estado==MINIMO)return area.x;
    else if(estado==MAXIMO)return areamax.x;
}

int Frame::getY(){
    if(estado==MINIMO)return area.y;
    else if(estado==MAXIMO)return areamax.y;
}

int Frame::getW(){
    if(estado==MINIMO)return area.w;
    else if(estado==MAXIMO)return areamax.w;
}

int Frame::getH(){
    if(estado==MINIMO)return area.h;
    else if(estado==MAXIMO)return areamax.h;
}

SDL_Rect Frame::getArea(){
    if(estado==MINIMO)return area;
    else if(estado==MAXIMO)return areamax;
}

Boton* Frame::getBcerrar(){
    return bcerrar;
}

Boton* Frame::getBmaxmin(){
    return bmaxmin;
}

Uint8 Frame::getEstado(){
    return estado;
}

