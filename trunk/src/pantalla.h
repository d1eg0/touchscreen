#ifndef PANTALLA_H
#define PANTALLA_H
#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
using namespace std;
class Pantalla
{
private:
	SDL_Surface* screen;
	int h_screen;
	int v_screen;
public:
	Pantalla();
	~Pantalla();

};
#endif

	
