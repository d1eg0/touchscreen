#ifndef GESTORESTADO_H
#define GESTORESTADO_H
#include <SDL/SDL_thread.h>
#include <SDL/SDL.h>
#include <stdlib.h>
using namespace std;
class GestorEstado{
public:
    GestorEstado();
    ~GestorEstado();
private:
    SDL_Thread *gestor;
    

};
#endif
