#ifndef CAMPO_H
#define CAMPO_H
#include <SDL/SDL.h>
#include <string>
#include "frame.h"

using namespace std;

class Campo  
{
public:
	Campo(Frame *frame, 
		string nombre, 
		float valor, 
		float vmax, 
		float vmin, 
		float incremento,
		bool estatico);
	virtual ~Campo();

	void cargarCampo(int x, int y,  Uint32 colorNombre, Uint32 colorValor);
	
	//void updateValor(float valor);


private:
	Frame *frame;

	string nombre;
	SDL_Rect arean;
	float valor;
	bool estatico;
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
