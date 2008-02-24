#include "radar.h"
#include <SDL/SDL_gfxPrimitives.h>
#include "constantes.h"
#include <SDL/SDL_rotozoom.h>
#include "silla.h"
extern SDL_mutex *bloqpantalla;
//extern int SCREEN_W,SCREEN_H;
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
    r[0]=(int)dif;
    r[1]=(int)(dif*2.0);
    r[2]=(int)(dif*3.0);
    if(SDL_MUSTLOCK(frame->getVentana()))SDL_LockSurface(frame->getVentana());
    circleColor(frame->getVentana(),xm,ym,r[0],color);
    circleColor(frame->getVentana(),xm,ym,r[1],color);
    circleColor(frame->getVentana(),xm,ym,r[2],color);

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
    extern SDL_mutex *semVideo;
    frame->activarFrame();
    xm=(int)(frame->getX()+(frame->getW()*0.5));
    ym=(int)(frame->getY()+(frame->getH()*0.5));
    float dif=frame->getH()/7.0;
    r[0]=(int)dif;
    r[1]=(int)(dif*2.0);
    r[2]=(int)(dif*3.0);
    SDL_mutexP(semVideo);
    if(SDL_MUSTLOCK(frame->getVentana()))SDL_LockSurface(frame->getVentana());
    circleColor(frame->getVentana(),xm,ym,r[0],color);
    circleColor(frame->getVentana(),xm,ym,r[1],color);
    circleColor(frame->getVentana(),xm,ym,r[2],color);
    //Etiquetas de escala
    Uint32 colorE=color&0xffffff80;
    char* escalapos[3]={"5","10","15"};
    char* escalaneg[3]={"-5","-10","-15"};
    int i;
    //+X
    for(i=0;i<3;i++){
	stringColor(
		frame->getVentana(),
		xm+r[i]+4, 
		ym-10, 
		escalapos[i], 
		colorE);
    }
    //-X
    for(i=0;i<3;i++){
	stringColor(
		frame->getVentana(),
		xm-r[i]-15-i*5, 
		ym-10, 
		escalaneg[i], 
		colorE);
    }
    //+Y
    for(i=0;i<3;i++){
	stringColor(
		frame->getVentana(),
		xm+4, 
		ym-r[i]-10, 
		escalapos[i], 
		colorE);
    }
    //-Y
    for(i=0;i<3;i++){
	stringColor(
		frame->getVentana(),
		xm+4, 
		ym+r[i]+3, 
		escalaneg[i], 
		colorE);
    }
    //Cruz del radar
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
    SDL_mutexV(semVideo);

}

int Radar::getX(){
    return xm;
}

int Radar::getY(){
    return ym;
}
int Radar::getR1(){
    return r[0];
}
int Radar::getR2(){
    return r[1];
}
int Radar::getR3(){
    return r[2];
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

//Hilo de escaner
int escan(void *r){
    extern SDL_mutex *mutexSincRadar;
    extern SDL_cond *condSincRadar;
    extern bool pauseRadar;
    extern SDL_mutex *semVideo;
    extern Silla *silla;
    Radar *escaner=(Radar*)r;
    Uint16 ang=90;
    while(1){
	SDL_mutexP(mutexSincRadar);
	    if(pauseRadar==true){
		SDL_CondWait(condSincRadar,mutexSincRadar);
	    }

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
	    
	}
	//Dibujar radar con degradado
	filledPieColor(escaner->getFrame()->getVentana(), escaner->getX(), escaner->getY(), escaner->getR3(), ang-90, ang, 0xff000050);
	filledPieColor(escaner->getFrame()->getVentana(), escaner->getX(), escaner->getY(), escaner->getR3(), ang-90, ang-75, 0xff000015);
	filledPieColor(escaner->getFrame()->getVentana(), escaner->getX(), escaner->getY(), escaner->getR3(), ang-90, ang-80, 0xff000015);
	filledPieColor(escaner->getFrame()->getVentana(), escaner->getX(), escaner->getY(), escaner->getR3(), ang-90, ang-85, 0xff000015);
	
	if(SDL_MUSTLOCK(escaner->getFrame()->getVentana()))SDL_UnlockSurface(escaner->getFrame()->getVentana());
	
	//Rotar la imagen
	SDL_Surface *flecha=rotozoomSurface (escaner->getFlecha(), silla->getRot(), 0.1, 1);
	//central la imagen	
	SDL_Rect desp=escaner->getDesp();
	desp.x=(Uint16)(escaner->getX()-(float)(flecha->w)*0.5);
	desp.y=(Uint16)(escaner->getY()-(float)(flecha->h)*0.5);
	//añadir transparencias
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
	SDL_Delay(20);//refresco

    }
    return 0;
}
