#ifndef PANTALLA_H
#define PANTALLA_H
#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "frame.h"
#include "punto.h"
using namespace std;



/**
 *  \class Pantalla
 *  \brief Gestiona todos los aspectos relacionados con el monitor (como la resoluci&oacute;n).
 *   
 *  \par 
 */
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
    /** Instancia de la pantalla */
    Pantalla(SDL_Surface *screen);

    ~Pantalla();
    /** Devuelve el puntero a la pantalla */
    SDL_Surface* getPantalla();
    /** Ocultar el cursor */
    void hideCursor();
    /** Gestiona la entrada del teclado */
    void entrada();
    /** Limpia la pantalla */
    void borrar();
    /** Oscurece la zona indicada */
    void setAlpha(Frame *frame, Uint8 zona);
    /** Devuelve si se ha salido del programa */
    bool salir();
    /** Minimiza las 3 ventanas */
    void minimizar();
    /** Modifica el valor de gestionar o no la entrada */ 
    void setHandle(bool handle);
};
#endif

	

