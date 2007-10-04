#ifndef BOTON_H
#define BOTON_H
#include <SDL/SDL.h>


enum EstadoBoton {activo=1, inactivo=0};

class Boton  
{
public:
	Boton(SDL_Surface *Ventana);
	virtual ~Boton();

	void cargarBoton(int x, int y, int w, int h, char *c, Uint32 color);
	//void CargarBoton(int x, int y, int w, int h,char *_text, Uint32 _Colorfons, SDL_Color *_Colortext);
	
	//void InsertarTexto(char *_text);
//	void dibujarBoton();

	bool presionado(int xm, int ym);
	bool getEstado();
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
