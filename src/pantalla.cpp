#include "pantalla.h"
#include "constantes.h"
#include "boton.h"
#include "mapa.h"
extern Boton *botonMasZoom, *botonMenosZoom;
extern Mapa plano;
extern Frame *framemapa;

Pantalla::Pantalla() 
{
    Uint8 video_bpp;
    Uint32 videoflags;
    videoflags = SDL_SWSURFACE | SDL_SRCALPHA | SDL_RESIZABLE;
    h_screen=SCREEN_H;
    v_screen=SCREEN_W;
    sdl_quit=false;
    info = SDL_GetVideoInfo();
    if ( info->vfmt->BitsPerPixel > 8 ) {
	video_bpp = info->vfmt->BitsPerPixel;
    } else {
	video_bpp = 16;
    }
    screen=SDL_SetVideoMode(v_screen, h_screen, video_bpp, videoflags);
//SDL_DOUBLEBUF|SDL_SWSURFACE);	
    SDL_SetAlpha(screen, SDL_SRCALPHA, 0);
    Dibujar paleta(screen);
    SDL_FillRect( screen, 0, 0x000000);
    SDL_UpdateRect(screen,0,0,0,0);
	//SDL_ShowCursor(0);	//ocultar cursor
}

Pantalla::~Pantalla() 
{
    SDL_Quit();
}


SDL_Surface* Pantalla::getPantalla()
{
	return screen;
}

void Pantalla::entrada() 
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
			double factor=100.0/plano.getEscala();
			double px=(event.motion.x-plano.getOX())*factor;
			double py=(-event.motion.y+plano.getOY())*factor;
			cout << "px:" << px << ", py:" << py << endl;
			if(botonMasZoom->presionado(event.motion.x,event.motion.y)){
				cout << "Z+dentro" << endl;
				framemapa->limpiarFrame();
				plano.escalarMapa(25);
				SDL_UpdateRect(screen,0,0,0,0);
			}else cout << "Zfuera" << endl;	
			if(botonMenosZoom->presionado(event.motion.x,event.motion.y)){
				cout << "Z-dentro" << endl;
				framemapa->limpiarFrame();
				plano.escalarMapa(-25);
				SDL_UpdateRect(screen,0,0,0,0);
			}else cout << "Zfuera" << endl;	
			if(framemapa->getBM()->presionado(event.motion.x,event.motion.y)){
				cout << "Mdentro" << endl;
				framemapa->cerrarFrame();
			}else cout << "Mfuera" << endl;	
		

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

bool Pantalla::salir()
{
	return sdl_quit;
}
