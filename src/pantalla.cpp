#include "pantalla.h"

Pantalla::Pantalla() {
	h_screen=480;
	v_screen=640;
	sdl_quit=false;
	screen=SDL_SetVideoMode(v_screen, h_screen, 16, SDL_DOUBLEBUF|SDL_SWSURFACE);	
	SDL_FillRect( screen, 0, SDL_MapRGB( screen->format, 200, 200, 200 ) );
	SDL_UpdateRect(screen,0,0,0,0);
	SDL_ShowCursor(0);	//ocultar cursor
}

Pantalla::~Pantalla() {
	SDL_Quit();
}

void Pantalla::Entrada() {
	SDL_Event event;
	SDL_WaitEvent(&event);
	//while ( SDL_PollEvent( &event ) ) 
	{
		switch ( event.type ) 
		{
		case SDL_KEYDOWN:
			//Escape presionado
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				cout << "teclado:scape" << endl;
				sdl_quit = true;
				break;
			}
 
			//KeyDown( event.key.keysym.sym );
			break;
 
		case SDL_QUIT:
			//Boton de salir
			sdl_quit = true;
			break;
 
		case SDL_MOUSEBUTTONDOWN:
			cout << "click" << endl;
			/*MouseButtonDown(
				event.button.button, 
				event.motion.x, 
				event.motion.y, 
				event.motion.xrel, 
				event.motion.yrel);*/
			cout << "x:" << event.motion.x << " y:" << event.motion.y <<  endl;
			if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)){
            	cout << "boton: izquierdo" << endl;
			}else if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(2)){
             	cout << "boton: medio" << endl;
			}else if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3)){
             	cout << "boton: derecho" << endl;
			}
			break;
 
		} 
	} 
}

bool Pantalla::Salir(){
	return sdl_quit;
}
