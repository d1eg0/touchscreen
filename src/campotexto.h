#ifndef CAMPOTEXTO_H
#define CAMPOTEXTO_H
#include <SDL/SDL.h>
#include <string>
#include "frame.h"

using namespace std;

class Campotexto  
{
public:
	Campotexto(Frame *frame, 
		string nombre, 
		float valor, 
		float vmax, 
		float vmin, 
		float incremento);
	virtual ~Campotexto();

	void cargarCampotexto(int x, int y,  Uint32 colorNombre, Uint32 colorValor);
	
	//void updateValor(float valor);


private:
	Frame *frame;

	string nombre;
	SDL_Rect arean;
	float valor;
	SDL_Rect areav;

	float minvalor;
	float maxvalor;
	float incremento;

	Uint32 colorNombre;
	Uint32 colorValor;


	Boton *bmas;
	Boton *bmenos;
};

#endif
