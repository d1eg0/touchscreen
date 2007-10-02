#ifndef ETIQUETA_H
#define ETIQUETA_H
#include <SDL/SDL.h>



class Etiqueta  
{
public:
	Etiqueta(SDL_Surface *Ventana);
	virtual ~Etiqueta();

	void cargarEtiqueta(int x, int y, int w, int h, char *c, Uint32 colorFuente, Uint32 colorBorde, Uint32 colorRelleno);
	//void CargarEtiqueta(int x, int y, int w, int h,char *_text, Uint32 _Colorfons, SDL_Color *_Colortext);
	
	//void InsertarTexto(char *_text);
	void dibujarEtiqueta();


     

private:
	SDL_Rect area;
	SDL_Rect contenedor;
	SDL_Surface *ventana;

	char *texto;
	Uint32 colorBorde;
	Uint32 colorFuente;
	Uint32 colorRelleno;

	//SDL_Color colorFuente;
	

};

#endif
