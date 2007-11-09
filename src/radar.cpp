#include "radar.h"
#include <SDL/SDL_gfxPrimitives.h>
#include "constantes.h"
extern SDL_mutex *bloqpantalla;
int escan(void *r);

Radar::Radar(Frame *frame){
    this->frame=frame;
    color=0x00FF7FFF;
    xm=(int)(frame->getX()+(frame->getW()*0.5));
    ym=(int)(frame->getY()+(frame->getH()*0.5));
    frame->activarFrame();
    float dif=frame->getH()/7.0;
    r1=(int)dif;
    r2=(int)(dif*2.0);
    r3=(int)(dif*3.0);
    if(SDL_MUSTLOCK(frame->getVentana()))SDL_LockSurface(frame->getVentana());
    circleColor(frame->getVentana(),xm,ym,r1,color);
    circleColor(frame->getVentana(),xm,ym,r2,color);
    circleColor(frame->getVentana(),xm,ym,r3,color);
    lineColor(frame->getVentana(),
	    frame->getX(),
	    ym,
	    frame->getX()+frame->getW(),
	    ym,
	    color);
    lineColor(frame->getVentana(),
	    xm,
	    frame->getY(),
	    xm,
	    frame->getY()+frame->getH(),
	    color);
    //filledPieColor(frame->getVentana(), xm, ym, r3, 0, 45, 0xff0000ff);
    if(SDL_MUSTLOCK(frame->getVentana()))SDL_UnlockSurface(frame->getVentana());
    SDL_UpdateRect(frame->getVentana(), 0, 0, SCREEN_W, SCREEN_H);
    s= SDL_CreateThread(escan, (void*)this);
}

Radar::~Radar(){
    lobstaculos.clear();
    SDL_KillThread(s);
}


void Radar::recargar(bool refresh){
    frame->activarFrame();
    xm=(int)(frame->getX()+(frame->getW()*0.5));
    ym=(int)(frame->getY()+(frame->getH()*0.5));
    float dif=frame->getH()/7.0;
    r1=(int)dif;
    r2=(int)(dif*2.0);
    r3=(int)(dif*3.0);
    if(SDL_MUSTLOCK(frame->getVentana()))SDL_LockSurface(frame->getVentana());
    circleColor(frame->getVentana(),xm,ym,r1,color);
    circleColor(frame->getVentana(),xm,ym,r2,color);
    circleColor(frame->getVentana(),xm,ym,r3,color);
    lineColor(frame->getVentana(),
	    frame->getX(),
	    ym,
	    frame->getX()+frame->getW(),
	    ym,
	    color);
    lineColor(frame->getVentana(),
	    xm,
	    frame->getY(),
	    xm,
	    frame->getY()+frame->getH(),
	    color);
    if(SDL_MUSTLOCK(frame->getVentana()))SDL_UnlockSurface(frame->getVentana());
    if(refresh)
	SDL_UpdateRect(frame->getVentana(), 0, 0, SCREEN_W, SCREEN_H);

}

int Radar::getX(){
    return xm;
}

int Radar::getY(){
    return ym;
}
int Radar::getR1(){
    return r1;
}
int Radar::getR2(){
    return r2;
}
int Radar::getR3(){
    return r3;
}
Frame *Radar::getFrame(){
    return frame;
}
int escan(void *r){
    Radar *escaner=(Radar*)r;
    Uint16 ang=90;
    while(1){
	escaner->getFrame()->limpiarFrame(false);
	escaner->recargar(false);
	escaner->getFrame()->activarFrame();
	if(SDL_MUSTLOCK(escaner->getFrame()->getVentana()))SDL_LockSurface(escaner->getFrame()->getVentana());
	filledPieColor(escaner->getFrame()->getVentana(), escaner->getX(), escaner->getY(), escaner->getR3(), ang-90, ang, 0xff000090);
	filledPieColor(escaner->getFrame()->getVentana(), escaner->getX(), escaner->getY(), escaner->getR3(), ang-90, ang-75, 0xff000020);
	filledPieColor(escaner->getFrame()->getVentana(), escaner->getX(), escaner->getY(), escaner->getR3(), ang-90, ang-80, 0xff000020);
	filledPieColor(escaner->getFrame()->getVentana(), escaner->getX(), escaner->getY(), escaner->getR3(), ang-90, ang-85, 0xff000020);
    if(SDL_MUSTLOCK(escaner->getFrame()->getVentana()))SDL_UnlockSurface(escaner->getFrame()->getVentana());
	SDL_UpdateRect(escaner->getFrame()->getVentana(), 0, 0, SCREEN_W, SCREEN_H);
	ang++;
	ang%=360;
	usleep(10000);
    }
    return 0;
}
