#include "pantalla.h"
#include "constantes.h"
#include "boton.h"
#include "mapa.h"
#include "etiqueta.h"
extern Boton *botonMasZoom, 
       *botonMenosZoom;
extern Boton *botonDerecha,
       *botonIzquierda,
       *botonArriba,
       *botonAbajo,
       *botonCentrar;
extern Mapa plano;
extern Frame *framemapa;
extern Etiqueta *e_zoom,*e_vzoom;

Pantalla::Pantalla() 
{
    Uint8 video_bpp;
    Uint32 videoflags;
    videoflags = SDL_SWSURFACE | SDL_SRCALPHA ;
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
				plano.escalarMapa(FACTOR_ZOOM);
				e_vzoom->insertarTexto(plano.getEscalaStr());
				SDL_UpdateRect(screen,0,0,0,0);
			}
			else if(botonMenosZoom->presionado(event.motion.x,event.motion.y)){
				cout << "Z-dentro" << endl;
				framemapa->limpiarFrame();
				plano.escalarMapa(-FACTOR_ZOOM);
				e_vzoom->insertarTexto(plano.getEscalaStr());
				SDL_UpdateRect(screen,0,0,0,0);
			}
			else if(botonDerecha->presionado(event.motion.x,event.motion.y)){
				cout << "Derecha" << endl;
				framemapa->limpiarFrame();
				plano.despDerecha();
				SDL_UpdateRect(screen,0,0,0,0);
			}
			else if(botonIzquierda->presionado(event.motion.x,event.motion.y)){
				cout << "Izquierda" << endl;
				framemapa->limpiarFrame();
				plano.despIzquierda();
				SDL_UpdateRect(screen,0,0,0,0);
			}
			else if(botonArriba->presionado(event.motion.x,event.motion.y)){
				cout << "Arriba" << endl;
				framemapa->limpiarFrame();
				plano.despArriba();
				SDL_UpdateRect(screen,0,0,0,0);
			}
			else if(botonAbajo->presionado(event.motion.x,event.motion.y)){
				cout << "Abajo" << endl;
				framemapa->limpiarFrame();
				plano.despAbajo();
				SDL_UpdateRect(screen,0,0,0,0);
			}
			else if(botonCentrar->presionado(event.motion.x,event.motion.y)){
				cout << "Centrar" << endl;
				framemapa->limpiarFrame();
				plano.centrarMapa(screen,framemapa);
				plano.pintarMapa(screen,framemapa,plano.getEscala());
				SDL_UpdateRect(screen,0,0,0,0);
			}
			else if(framemapa->getBcerrar()->presionado(event.motion.x,event.motion.y)){
				cout << "Bcerrar" << endl;
				framemapa->cerrarFrame();
				this->borrar();
			}	
			else if(framemapa->getBmaxmin()->presionado(event.motion.x,event.motion.y)){
				cout << "Bmaxmin" << endl;
				this->borrar();
				if(framemapa->getEstado()==MINIMO){
				    framemapa->maxFrame();
				    plano.pintarMapa(screen,framemapa,plano.getEscala());
				    //Botones Zoom
				    botonMasZoom->cargarBoton(framemapa->getX()+framemapa->getW()-100, framemapa->getY()+framemapa->getH()+30, 20,20,"+",0xFFA500FF);
				    botonMenosZoom->cargarBoton(framemapa->getX()+framemapa->getW()-50, framemapa->getY()+framemapa->getH()+30, 20,20,"-",0xFFA500FF);

				    //Etiqueta Zoom
				    e_zoom->cargarEtiqueta(framemapa->getX()+framemapa->getW()-100,	    
					    framemapa->getY()+framemapa->getH()+10,
					    70,
					    20,
					    "Zoom",
					    0xFFA500FF,
					    0x000000FF,
					    0x000000FF);

				    e_vzoom->cargarEtiqueta(framemapa->getX()+framemapa->getW()-100,
					    framemapa->getY()+framemapa->getH()+50,
					    70,
					    20,
					    plano.getEscalaStr(),
					    0xFFA500FF,
					    0xFFA500FF,
					    0x000000FF);
    
				    //Botones movimiento del mapa

				    //	Derecha
				    botonDerecha->cargarBoton(framemapa->getX()+140, 
					    framemapa->getY()+framemapa->getH()+30, 
					    20,
					    20,
					    ">",
					    0xFFA500FF);
				    //	Izquierda
				    botonIzquierda->cargarBoton(framemapa->getX()+100, 
					    framemapa->getY()+framemapa->getH()+30, 
					    20,
					    20,
					    "<",
					    0xFFA500FF);
				    //	Arriba
				    botonArriba->cargarBoton(framemapa->getX()+120, 
					    framemapa->getY()+framemapa->getH()+10, 
					    20,
					    20,
					    "^",
					    0xFFA500FF);
				    //	Abajo
				    botonAbajo->cargarBoton(framemapa->getX()+120, 
					    framemapa->getY()+framemapa->getH()+50, 
					    20,
					    20,
					    "V",
					    0xFFA500FF);
				    //	Centrar
				    botonCentrar->cargarBoton(framemapa->getX()+120, 
					    framemapa->getY()+framemapa->getH()+30, 
					    20,
					    20,
					    "C",
					    0xFFA500FF);
				}else{ 
				    framemapa->minFrame(); 
				    plano.pintarMapa(screen,framemapa,plano.getEscala());
				    //Botones Zoom
				    botonMasZoom->cargarBoton(framemapa->getX()+framemapa->getW()-100, 
					    framemapa->getY()+framemapa->getH()+30, 
					    20,
					    20,
					    "+",
					    0xFFA500FF);
				    botonMenosZoom->cargarBoton(framemapa->getX()+framemapa->getW()-50, 
					    framemapa->getY()+framemapa->getH()+30, 
					    20,
					    20,
					    "-",
					    0xFFA500FF);

				    //Etiqueta Zoom
				    e_zoom->cargarEtiqueta(framemapa->getX()+framemapa->getW()-100,	    
					    framemapa->getY()+framemapa->getH()+10,
					    70,
					    20,
					    "Zoom",
					    0xFFA500FF,
					    0x000000FF,
					    0x000000FF);
				    e_vzoom->cargarEtiqueta(framemapa->getX()+framemapa->getW()-100,
					    framemapa->getY()+framemapa->getH()+50,
					    70,
					    20,
					    plano.getEscalaStr(),
					    0xFFA500FF,
					    0xFFA500FF,
					    0x000000FF);
    
				    //Botones movimiento del mapa

				    //	Derecha
				    botonDerecha->cargarBoton(framemapa->getX()+140, 
					    framemapa->getY()+framemapa->getH()+30, 
					    20,
					    20,
					    ">",
					    0xFFA500FF);
				    //	Izquierda
				    botonIzquierda->cargarBoton(framemapa->getX()+100, 
					    framemapa->getY()+framemapa->getH()+30, 
					    20,
					    20,
					    "<",
					    0xFFA500FF);
				    //	Arriba
				    botonArriba->cargarBoton(framemapa->getX()+120, 
					    framemapa->getY()+framemapa->getH()+10, 
					    20,
					    20,
					    "^",
					    0xFFA500FF);
				    //	Abajo
				    botonAbajo->cargarBoton(framemapa->getX()+120, 
					    framemapa->getY()+framemapa->getH()+50, 
					    20,
					    20,
					    "V",
					    0xFFA500FF);
				    //	Centrar
				    botonCentrar->cargarBoton(framemapa->getX()+120, 
					    framemapa->getY()+framemapa->getH()+30, 
					    20,
					    20,
					    "C",
					    0xFFA500FF);

				}
				SDL_UpdateRect(screen,0,0,0,0);
			}	
		

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

void Pantalla::borrar(){
    SDL_Rect r;
    r.x=0;
    r.y=0;
    r.w=SCREEN_W;
    r.h=SCREEN_H;
    SDL_SetClipRect(screen,&r);
    SDL_FillRect( screen, 0, 0x000000);
    SDL_UpdateRect(screen,0,0,0,0);
}

bool Pantalla::salir()
{
	return sdl_quit;
}
