#include "objetivo.h"
#include "linea.h"
#include "polilinea.h"
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL.h>
Objetivo::Objetivo(Frame *frame, double xp, double yp){
    this->frame=frame;
    this->xp=xp;
    this->yp=yp;
    this->radio=5;
}

Objetivo::~Objetivo(){}

bool Objetivo::interior(Polilinea polilinea){
    int nc=0;
    double da,db,alfa,xq;
    vector<Linea> vLados;
    vLados.clear();
    vLados=polilinea.toLineas();
    vector<Linea>::iterator i_lado;
    for(i_lado=vLados.begin(); i_lado!=vLados.end(); i_lado++){
	da=(*i_lado).getY1()-this->yp;
	db=(*i_lado).getY2()-this->yp;
	if ((da>=0 && db<0) || (db>=0 && da<0)){
	    alfa=da/(da-db);
	    xq=(*i_lado).getX1()+alfa*(
		    (*i_lado).getX2()-(*i_lado).getX1());
	    if(xq>this->xp)nc++;
	}

    }
    if(nc%2==0)	{
	cout << "objetivo fuera" << endl;
	return false;
    }else {
	cout << "objetivo dentro" << endl;
	return true;
    }
}

void Objetivo::dibujar(int x, int y,bool zvalida){
    SDL_Rect r=frame->getArea();
    SDL_SetClipRect(frame->getVentana(),&r);
    filledCircleColor(frame->getVentana(), x, y, radio, 0xff0000ff);
    SDL_UpdateRect(frame->getVentana(),0,0,0,0);
}

