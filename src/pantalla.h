#ifndef PANTALLA_H
#define PANTALLA_H
#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "frame.h"
#include "punto.h"
using namespace std;
class Pantalla
{
private:
    SDL_Surface* screen;
    int h_screen;
    int v_screen;
    bool sdl_quit,
	 //alpha,
	 handle,
	 pcontestada;
    const SDL_VideoInfo *info;

public:
    Pantalla(SDL_Surface *screen);
    ~Pantalla();

    SDL_Surface* getPantalla();
    void hideCursor();
    void entrada();
    void borrar();
    void setAlpha(Frame *frame, Uint8 zona);
    bool salir();
    void minimizar();
    void setHandle(bool handle);
};
#endif

	

