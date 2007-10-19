#ifndef PANTALLA_H
#define PANTALLA_H
#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
using namespace std;
class Pantalla
{
private:
    SDL_Surface* screen;
    int h_screen;
    int v_screen;
    bool sdl_quit;
    const SDL_VideoInfo *info;

public:
    Pantalla();
    ~Pantalla();

    SDL_Surface* getPantalla();
    void entrada();
    void borrar();
    void alpha();
    bool salir();


};
#endif

	

