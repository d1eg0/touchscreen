#ifndef GESTORESTADO_H
#define GESTORESTADO_H
#include <SDL/SDL_thread.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "clientecapa_baja.h"

/**
 *  \class GestorEstado
 *  \brief Hilo que realiza la lectura de los valores de los sensores cuando se reciben
 *   
 *  \par 
 */

using namespace std;
class GestorEstado{
public:
    GestorEstado();
    ~GestorEstado();
private:
    SDL_Thread *gestor;
    

};
#endif
