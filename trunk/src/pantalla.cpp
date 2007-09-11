#include "pantalla.h"

Pantalla::Pantalla() {
	h_screen=480;
	v_screen=640;
	screen=SDL_SetVideoMode(v_screen, h_screen, 16, SDL_DOUBLEBUF|SDL_SWSURFACE);	
	SDL_FillRect( screen, 0, SDL_MapRGB( screen->format, 200, 200, 200 ) );
	SDL_UpdateRect(screen,0,0,0,0);
}

Pantalla::~Pantalla() {
	SDL_Quit();
}
