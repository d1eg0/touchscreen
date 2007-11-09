#include "objetivo.h"
#include "linea.h"
#include "polilinea.h"
#include "constantes.h"
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL.h>
#include <iostream>
#include <sstream>
Objetivo::Objetivo(){
    ofijado=false;
    this->pregunta=false;
}
    
Objetivo::Objetivo(Frame *frame, Mapa *plano, double xp, double yp){
    this->setObjetivo(frame,plano,xp,yp);
}

Objetivo::~Objetivo(){}

void Objetivo::setObjetivo(Frame *frame, Mapa *plano, double xp, double yp){
    this->frame=frame;
    this->plano=plano;
    this->xp=xp;
    this->yp=yp;
    this->radio=3;
    bsi=new Boton(frame->getVentana());
    bno=new Boton(frame->getVentana());
}

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
	return false;
    }else {
	return true;
    }
}

void Objetivo::dibujar(){
    int tradio;
    SDL_Rect r=frame->getArea();
    if(SDL_MUSTLOCK(frame->getVentana()))SDL_LockSurface(frame->getVentana());
    SDL_SetClipRect(frame->getVentana(),&r);
    tradio=(int)(radio*(plano->getEscala()/100.0)); 
    Uint32 color;
    if(valido)color=0x00ff00ff;
    else color=0xff0000ff;
    
    Punto o(xp,yp);
    o.cpantalla(frame,plano->getDH(),plano->getDV(),plano->getEscala());
    filledCircleColor(frame->getVentana(), (int)o.getX(), (int)o.getY(), tradio, color);
    filledCircleColor(frame->getVentana(), (int)o.getX(), (int)o.getY(), tradio-1, 0xffffffff);
    if(SDL_MUSTLOCK(frame->getVentana()))SDL_UnlockSurface(frame->getVentana());
    SDL_UpdateRect(frame->getVentana(),0,0,0,0);
}

void Objetivo::activar(){
    ofijado=true;
}

void Objetivo::desactivar(){
    ofijado=false;
}

bool Objetivo::getFijado(){
    return ofijado;
}

void Objetivo::setValido(bool valido){
    this->valido=valido;
}

bool Objetivo::getValido(){
    return valido;
}

double Objetivo::getX(){
    return xp;
}

double Objetivo::getY(){
    return yp;
}

void Objetivo::preguntar(){
    Punto o(xp,yp);
    o.cpantalla(frame,plano->getDH(),plano->getDV(),plano->getEscala());
    double x1=o.getX()-SIZE_C*4;
    double x2=(x1+4*SIZE_C)+SIZE_C*4;
    double y1=o.getY()+SIZE_C*2;
    //Corregir la posicion de la etiqueta
    if(x2>frame->getX()+frame->getW()){
	x1-=x2-(frame->getX()+frame->getW());
    }
    if(x1<frame->getX()){
	x1=frame->getX();
    }
    if(y1<frame->getY()){
	y1=frame->getY();
    }
    if(y1>frame->getY()+frame->getH()){
	y1=frame->getY()+frame->getH()-SIZE_C*2;
    }
    Uint32 colorbotones=0x4682B4FF;	
    bsi->cargarBoton(
	    (int)x1,
	    (int)y1,
	    SIZE_C*4,
	    SIZE_C*2,
	    "Si",
	    colorbotones);
    bno->cargarBoton(
	    (int)x1+SIZE_C*4,
	    (int)y1,
	    SIZE_C*4,
	    SIZE_C*2,
	    "No",
	    colorbotones);
    pregunta=true;
}

int Objetivo::respuesta(int x, int y){
    if (bsi->presionado(x,y))return RESPUESTA_SI;
    if (bno->presionado(x,y))return RESPUESTA_NO;
    return SIN_RESPUESTA;
}

bool Objetivo::preguntado(){
    return pregunta;
}

void Objetivo::nopreguntar(){
    pregunta=false;
}

void Objetivo::load(){
    xp=xp_temp;
    yp=yp_temp;
    valido=valido_temp;
}

void Objetivo::store(){
    xp_temp=xp;
    yp_temp=yp;
    valido_temp=valido;
}

string Objetivo::toString(){
    string xpstr,ypstr;
    stringstream buffer;
    buffer.clear(); 
    buffer << xp;
    buffer >> xpstr;

    buffer.clear(); 
    buffer << yp;
    buffer >>ypstr;
    
    return xpstr+" "+ypstr;
}

