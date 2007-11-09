#ifndef GESTORCAMINO_H
#define GESTORCAMINO_H
#include <SDL/SDL_thread.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include "frame.h"
using namespace std;
class GestorCamino{
public:
    GestorCamino(SDL_Surface* surface);
    ~GestorCamino();
private:
    SDL_Thread *gestor;
    SDL_Surface *screen; 

};
#endif