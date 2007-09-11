#include "pantalla.h"

Pantalla::Pantalla() {
	Screen=SDL_SetVideoMode(640, 480, 16, SDL_DOUBLEBUF|SDL_SWSURFACE);
}

Pantalla::~Pantalla() {
	SDL_Quit();
}
