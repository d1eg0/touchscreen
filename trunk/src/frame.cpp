#include "frame.h"
#include "constantes.h"

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

void Frame::CargarFrame(int x, int y, int w, int h, Uint32 color)
{
	int wt, ht;
	this->color=color;
	area.h=h;
	area.w=w;
	area.x=x;
	area.y=y;
	//TTF_SizeText(Font,_texto,&wt,&ht);

	contenedor.x=area.x + ((w - wt)/2);
	contenedor.y=area.y + ((h - ht)/2);
	contenedor.w=wt;
	contenedor.h=ht;
	SDL_SetClipRect(ventana, &area);
	SDL_FillRect(ventana, &area, color);
	SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
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

