#ifndef BOTON_H
#define BOTON_H
#include <SDL/SDL.h>


enum EstadoBoton {seleccionado=1, deseleccionado=0};

class Boton  
{
public:
	Boton(SDL_Surface *Ventana);
	virtual ~Boton();

	void CargarBoton(int x, int y, int w, int h, Uint32 color);
	//void CargarBoton(int x, int y, int w, int h,char *_text, Uint32 _Colorfons, SDL_Color *_Colortext);
	
	//void InsertarTexto(char *_text);
	void DibujarBoton();

	bool Presionado(int xm, int ym);

	//int GetX();
	//int GetY();
	//int GetW();
	//int GetH();
     

private:
	SDL_Rect area;
	SDL_Surface *ventana;
	char *texto;
	Uint32 color;

	//SDL_Surface *SurfaceF;
	//TTF_Font *fuente;
	SDL_Color colorFuente;
	int Sizef;
	int Stylef;
	SDL_Rect contenedor;
	
	EstadoBoton estado;

};

#endif
