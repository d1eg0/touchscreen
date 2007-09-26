#include "pantalla.h"
#include "constantes.h"
#include "boton.h"
extern Boton *boton1;
Pantalla::Pantalla() 
{
	h_screen=SCREEN_H;
	v_screen=SCREEN_W;
	sdl_quit=false;
	screen=SDL_SetVideoMode(v_screen, h_screen, 16, SDL_DOUBLEBUF|SDL_SWSURFACE);	
	SDL_FillRect( screen, 0, SDL_MapRGB( screen->format, 200, 200, 200 ) );
	SDL_UpdateRect(screen,0,0,0,0);
	//SDL_ShowCursor(0);	//ocultar cursor
}

Pantalla::~Pantalla() 
{
	SDL_Quit();
}


SDL_Surface* Pantalla::GetPantalla()
{
	return screen;
}

void Pantalla::Entrada() 
{
	SDL_Event event;
	SDL_WaitEvent(&event);
	//while ( SDL_PollEvent( &event ) ) 
	{
		switch ( event.type ) 
		{
		case SDL_KEYDOWN:
			//Escape presionado
			switch (event.key.keysym.sym)
			{
			    case SDLK_ESCAPE :
			
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
			cout << "x:" << event.motion.x << " y:" << event.motion.y <<  endl;
			if(boton1->Presionado(event.motion.x,event.motion.y)){
				cout << "dentro" << endl;
			}else cout << "fuera" << endl;	
		

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

bool Pantalla::Salir()
{
	return sdl_quit;
}
