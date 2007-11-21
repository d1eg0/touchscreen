#include "radar.h"
#include <SDL/SDL_gfxPrimitives.h>
#include "constantes.h"
#include <SDL/SDL_rotozoom.h>
extern SDL_mutex *bloqpantalla;
int escan(void *r);

Radar::Radar(Frame *frame){
    this->frame=frame;
    //Flecha
    SDL_Surface *flechatemp=SDL_LoadBMP( "img/flecha.bmp" ); 
    flecha=SDL_DisplayFormat(flechatemp);
    SDL_FreeSurface( flechatemp );
    rot=0;
    color=0x00FF7FFF;
    xm=(int)(frame->getX()+(frame->getW()*0.5));
    ym=(int)(frame->getY()+(frame->getH()*0.5));
    desp.x=(Uint16)(xm-(float)(flecha->w)*0.5);
    desp.y=(Uint16)(ym-(float)(flecha->h)*0.5);
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

void Radar::dibujarFlecha(int rot){
    extern SDL_mutex *semVideo;
    SDL_Surface *flecha=NULL;
    SDL_Surface *flechaopt=NULL;
    SDL_Rect offset; 
    offset.x=100;
    offset.y=100;
    //flecha
    
    //if(SDL_MUSTLOCK(flecha))SDL_LockSurface(flecha);
    //boxColor(flecha,0,0,100,100,0x00ffffff);
    //if(SDL_MUSTLOCK(flecha))SDL_UnlockSurface(flecha);
    //añadirla
    SDL_mutexP(semVideo);
     flecha=SDL_LoadBMP( "img/flecha.bmp" ); 
   // flecha=IMG_Load("flecha.bmp");
    flechaopt=SDL_DisplayFormat(flecha);
    Uint32 colorkey = SDL_MapRGB( flechaopt->format, 0xff, 0xff, 0xff );
    SDL_SetColorKey( flechaopt, SDL_SRCCOLORKEY, colorkey );
    SDL_Rect r;
    r.x=0;
    r.y=0;
    r.w=SCREEN_W;
    r.h=SCREEN_H;
    SDL_SetClipRect(this->getFrame()->getVentana(),&r);
    if(SDL_MUSTLOCK(this->getFrame()->getVentana()))SDL_LockSurface(this->getFrame()->getVentana());
    SDL_BlitSurface( flechaopt, NULL, this->getFrame()->getVentana(), &offset );
    if(SDL_MUSTLOCK(this->getFrame()->getVentana()))SDL_UnlockSurface(this->getFrame()->getVentana());
    SDL_mutexV(semVideo);

}

SDL_Surface *Radar::getFlecha(){
    return flecha;
}
SDL_Rect Radar::getDesp(){
    return desp;
}
int Radar::getRot(){
    return rot++;
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
	SDL_Rect desp=escaner->getDesp();
	SDL_Surface *flecha=rotozoomSurface (escaner->getFlecha(), escaner->getRot(), 0.1, 1);
	desp.x=(Uint16)(escaner->getX()-(float)(flecha->w)*0.5);
	desp.y=(Uint16)(escaner->getY()-(float)(flecha->h)*0.5);
	//SDL_Surface *flecha=escaner->getFlecha();
	Uint32 colorkey = SDL_MapRGB( flecha->format, 0x00, 0x00, 0x00 );
	SDL_SetColorKey( flecha, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey );
	SDL_SetAlpha(flecha, SDL_SRCALPHA|SDL_RLEACCEL, 150);

	SDL_BlitSurface( flecha, NULL, escaner->getFrame()->getVentana(), &desp );
	SDL_FreeSurface( flecha );
	SDL_mutexV(semVideo);
	escaner->getFrame()->refrescarFrame();
	ang++;
	ang%=360;
	SDL_mutexV(mutexSincRadar);
	SDL_Delay(20);
    }
    return 0;
}
