#ifndef FRAME_H
#define FRAME_H
#include <SDL/SDL.h>
#include "boton.h"
//enum EstadoBoton {seleccionado=1, deseleccionado=0};

class Frame  
{
public:
	Frame(SDL_Surface *Ventana);
	virtual ~Frame();

	void cargarFrame(int x, int y, int w, int h,char *c, Uint32 color);
	//void CargarBoton(int x, int y, int w, int h,char *_text, Uint32 _Colorfons, SDL_Color *_Colortext);
	
    void cerrarFrame();
    void limpiarFrame();

    bool Presionado(int xm, int ym);
    SDL_Surface* getVentana();
    int getX();
    int getY();
    int getW();
    int getH();
    SDL_Rect getArea();
    Boton* getBM();
    Boton* getBm();
    Uint8 cambiarEstado();
private:
	SDL_Rect area;
	SDL_Surface *ventana;
	Uint32 color;
	SDL_Rect contenedor;
	Boton *max;
	Boton *min;
	Uint8 estado;

};

#endif
