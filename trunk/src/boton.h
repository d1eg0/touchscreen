#ifndef BOTON_H
#define BOTON_H
#include <SDL/SDL.h>


enum EstadoBoton {activo=1, inactivo=0, z=3};

class Boton  
{
public:
	Boton(SDL_Surface *Ventana);
	virtual ~Boton();

	void cargarBoton(int x, int y, int w, int h, char *c, Uint32 color);
	void recargarBoton();
	//void CargarBoton(int x, int y, int w, int h,char *_text, Uint32 _Colorfons, SDL_Color *_Colortext);
	
	//void InsertarTexto(char *_text);
//	void dibujarBoton();

	bool presionado(int xm, int ym);
	bool getEstado();
	//int GetX();
	//int GetY();
	//int GetW();
	//int GetH();
	void desactivar();     
	void borrar();

private:
	SDL_Rect area;
	SDL_Surface *ventana;
	char *texto;
	Uint32 color;

	SDL_Surface *surfacef;
	SDL_Color colorFuente;
	int Sizef;
//	int Stylef;
	SDL_Rect contenedor;
	
	EstadoBoton estado;

};

#endif
