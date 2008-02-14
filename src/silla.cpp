#include "silla.h"

Silla::Silla(Frame *frame, Mapa *plano){
    this->frame=frame;
    this->plano=plano;
    radio=3;
    rot=0;
}

Silla::~Silla(){
}

Punto Silla::getPos(){
    return pos;
}

void Silla::setPos(Punto pos){
    this->pos=pos;
}

int Silla::getRot(){
    extern SDL_mutex *mutexRot;
    SDL_mutexP(mutexRot);
    rot++;
    rot%=360;
    int rotacion=rot;
    SDL_mutexV(mutexRot);
    return rotacion;
}

void Silla::setRot(int r){
    extern SDL_mutex *mutexRot;
    SDL_mutexP(mutexRot);
    rot+=r;
    SDL_mutexV(mutexRot);
}

void Silla::dibujar(){
    int tradio;
    SDL_Rect r=frame->getArea();
    extern SDL_mutex *semVideo;
    SDL_mutexP(semVideo);
    if(SDL_MUSTLOCK(frame->getVentana()))SDL_LockSurface(frame->getVentana());
    SDL_SetClipRect(frame->getVentana(),&r);
    tradio=(int)(radio*(plano->getEscala()/100.0)); 
    Uint32 color;
    color=0x0000ffff;
    
   
    Punto o=pos;
    o.cpantalla(frame,plano->getDH(),plano->getDV(),plano->getEscala());
    filledCircleColor(frame->getVentana(), (int)o.getX(), (int)o.getY(), tradio, color);
    filledCircleColor(frame->getVentana(), (int)o.getX(), (int)o.getY(), tradio-2, 0xffffffff);
    filledCircleColor(frame->getVentana(), (int)o.getX(), (int)o.getY(), tradio-4, color);
    filledCircleColor(frame->getVentana(), (int)o.getX(), (int)o.getY(), tradio-6, 0xffffffff);
    if(SDL_MUSTLOCK(frame->getVentana()))SDL_UnlockSurface(frame->getVentana());
//    SDL_UpdateRect(frame->getVentana(),(int)o.getX()-tradio,(int)o.getY()-tradio,tradio*3,tradio*2);
    SDL_mutexV(semVideo);

}
