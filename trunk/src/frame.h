#ifndef FRAME_H
#define FRAME_H
#include <SDL/SDL.h>
#include "boton.h"
//enum EstadoBoton {seleccionado=1, deseleccionado=0};

class Frame  
{
public:
    Frame(SDL_Surface *ventana);
    virtual ~Frame();

    void cargarFrame(int x, int y, int w, int h,char *c, Uint32 color);
	//void CargarBoton(int x, int y, int w, int h,char *_text, Uint32 _Colorfons, SDL_Color *_Colortext);
	
    void cerrarFrame();
    void maxFrame(int x, int y, int w,int h);
    void minFrame();
    void desactivarFrame();
    void limpiarFrame(bool refresh);
    void activarFrame();
    void refrescarFrame();

    bool Presionado(int xm, int ym);
    SDL_Surface* getVentana();
    int getX();
    int getY();
    int getW();
    int getH();
    SDL_Rect getArea();
    Boton* getBcerrar();
    Boton* getBmaxmin();
    Uint8 getEstado();
    int getXc();
    int getYcDown();
    int getYc();

private:
    char* titulo;
    SDL_Rect area,areamax;
    SDL_Surface *ventana;
    SDL_Surface *frame;
    Uint32 color;
    SDL_Rect contenedor,contenedormax;
    Boton *bcerrar;
    Boton *bmaxmin;
    Uint8 estado;
    int xc,yc;//cordenadas de los campos

};

#endif
