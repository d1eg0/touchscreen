#ifndef FRAME_H
#define FRAME_H
#include <SDL/SDL.h>

//enum EstadoBoton {seleccionado=1, deseleccionado=0};

class Frame  
{
public:
	Frame(SDL_Surface *Ventana);
	virtual ~Frame();

	void CargarFrame(int x, int y, int w, int h, Uint32 color);
	//void CargarBoton(int x, int y, int w, int h,char *_text, Uint32 _Colorfons, SDL_Color *_Colortext);
	
	//void InsertarTexto(char *_text);

    bool Presionado(int xm, int ym);

    int getX();
    int getY();
    int getW();
    int getH();
    SDL_Rect getArea();
private:
	SDL_Rect area;
	SDL_Surface *ventana;
	//char *texto;
	Uint32 color;
	//SDL_Surface *SurfaceF;
	//TTF_Font *fuente;
	//SDL_Color colorFuente;
	//int Sizef;
	//int Stylef;
	SDL_Rect contenedor;
	
	//EstadoBoton estado;

};

#endif
