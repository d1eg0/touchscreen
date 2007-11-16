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
    if ( s == NULL ) {
        fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
        exit(1);
    }

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

vector<Punto> Radar::getObstaculos(){
    vector<Punto> lo;
    extern SDL_mutex *mutexObstaculo;
    SDL_mutexP(mutexObstaculo);
    lo = lobstaculos;
    SDL_mutexV(mutexObstaculo);
    return lo;
}

void Radar::addObstaculo(Punto o){
    extern SDL_mutex *mutexObstaculo;
    SDL_mutexP(mutexObstaculo);
    lobstaculos.push_back(o);
    SDL_mutexV(mutexObstaculo);
}

int escan(void *r){
    extern SDL_mutex *mutexSincRadar;
    extern SDL_cond *condSincRadar;
    extern bool pauseRadar;
    extern SDL_mutex *semVideo;
    Radar *escaner=(Radar*)r;
    Uint16 ang=90;
//    SDL_Delay(1000);
    while(1){
	SDL_mutexP(mutexSincRadar);
	    if(pauseRadar)SDL_CondWait(condSincRadar,mutexSincRadar);
	SDL_mutexV(mutexSincRadar);
	escaner->getFrame()->limpiarFrame(false);
	escaner->recargar(false);
	escaner->getFrame()->activarFrame();
	SDL_mutexP(semVideo);

	if(SDL_MUSTLOCK(escaner->getFrame()->getVentana()))SDL_LockSurface(escaner->getFrame()->getVentana());
	vector<Punto> lobstaculos=escaner->getObstaculos();
	vector<Punto>::iterator i;
	for(i=lobstaculos.begin();i!=lobstaculos.end();i++){
	    //cout << "x:" << (*i).getX() << " y:" << (*i).getY() << endl;
	    filledCircleColor(
		    escaner->getFrame()->getVentana(),
		    (int)(*i).getX()+escaner->getX(),
		    (int)(*i).getY()+escaner->getY(),
		    3,
		    0xffa500ff);
	    
	    //SDL_Delay(20000);
	}
	filledPieColor(escaner->getFrame()->getVentana(), escaner->getX(), escaner->getY(), escaner->getR3(), ang-90, ang, 0xff000090);
	filledPieColor(escaner->getFrame()->getVentana(), escaner->getX(), escaner->getY(), escaner->getR3(), ang-90, ang-75, 0xff000020);
	filledPieColor(escaner->getFrame()->getVentana(), escaner->getX(), escaner->getY(), escaner->getR3(), ang-90, ang-80, 0xff000020);
	filledPieColor(escaner->getFrame()->getVentana(), escaner->getX(), escaner->getY(), escaner->getR3(), ang-90, ang-85, 0xff000020);
	
	if(SDL_MUSTLOCK(escaner->getFrame()->getVentana()))SDL_UnlockSurface(escaner->getFrame()->getVentana());
	SDL_mutexV(semVideo);
//	SDL_UpdateRect(escaner->getFrame()->getVentana(), 0, 0, SCREEN_W, SCREEN_H);
	escaner->getFrame()->refrescarFrame();
	ang++;
	ang%=360;
	SDL_Delay(20);
    }
    return 0;
}
