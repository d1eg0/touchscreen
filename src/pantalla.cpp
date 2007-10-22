#include "pantalla.h"
#include "constantes.h"
#include "boton.h"
#include "mapa.h"
#include "etiqueta.h"
#include "objetivo.h"
#include <sstream>
extern Boton *botonMasZoom, 
       *botonMenosZoom;
extern Boton *botonDerecha,
       *botonIzquierda,
       *botonArriba,
       *botonAbajo,
       *botonCentrar;
extern Mapa plano;
extern Frame *framemapa,
       *frameradar,
       *framestado;
extern Etiqueta *e_zoom,*e_vzoom;
extern Objetivo objetivo;
Pantalla::Pantalla() 
{
    Uint8 video_bpp;
    Uint32 videoflags;
    videoflags = SDL_SWSURFACE | SDL_SRCALPHA | SDL_FULLSCREEN;
    h_screen=SCREEN_H;
    v_screen=SCREEN_W;
    sdl_quit=false;
    alpha=false;
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

//    SDL_ShowCursor(SDL_DISABLE);	//ocultar cursor
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
	    if(framemapa->Presionado(event.motion.x,event.motion.y)){
		objetivo.setObjetivo(framemapa,px,py);
		Polilinea contorno=plano.getCapa("CapaContorn")->getPolilinea()->front();
		if(objetivo.interior(contorno)){
		    vector<Polilinea> *obstaculos=plano.getCapa("CapaObstacles")->getPolilinea();
		    bool obstaculo=false;
		    vector<Polilinea>::iterator i_obstaculo;
		    for(i_obstaculo=obstaculos->begin();i_obstaculo!=obstaculos->end();i_obstaculo++){
			if(objetivo.interior((*i_obstaculo))){
			    obstaculo=true;
			    break;
			}
		    }
		    string pregunta;
		    bool pos_correcta;
		    Uint32 color_etiq;
		    if(obstaculo){
			cout << "error: obstaculo" << endl;
			pregunta = "obstaculo!";//msg
			pos_correcta=false;//posicion incorrecta
			this->setAlpha(framemapa,Z_CENTRO);//efecto alpha
			color_etiq=0xFF0000FF;//color
		    }else{
			ostringstream buffer;//msg
			buffer << "X:" << px<< " Y:" << py;//msg
			pregunta=buffer.str();//msg
			this->setAlpha(framemapa,Z_ABAJO);//efecto alpha
			//plano.pintarMapa(screen,framemapa,plano.getEscala());
			pos_correcta=true;//posicion correcta
			color_etiq=0x5757FFFF;//color
			botonMasZoom->desactivar();
			botonMenosZoom->desactivar();
		    }
		    objetivo.dibujar(event.motion.x,event.motion.y,pos_correcta);

		    //Posicion de la etiqueta pregunta
		    int x1=event.motion.x-50;
		    int x2=x1+pregunta.size()*SIZE_C+10;
		    int y1=event.motion.y-50;
		    //Corregir la posicion de la etiqueta
		    if(x2>framemapa->getX()+framemapa->getW()){
			x1-=x2-(framemapa->getX()+framemapa->getW());
		    }
		    if(x1<framemapa->getX()){
			x1=framemapa->getX();
		    }
		    if(y1<framemapa->getY()){
			y1=framemapa->getY();
		    }

		    Etiqueta *epregunta;
		    epregunta=new Etiqueta(screen);
		    epregunta->cargarEtiqueta(
			    x1,
			    y1,
			    pregunta.size()*SIZE_C+10,
			    SIZE_C*2,
			    (char*)pregunta.c_str(),
			    color_etiq,
			    color_etiq,
			    0x00000043);
		    SDL_UpdateRect(screen,0,0,0,0);


		    cout << "\tpx:" << px << ", py:" << py << endl;
		}
	    }
	    if(botonMasZoom->presionado(event.motion.x,event.motion.y)){
	        if(plano.getEscala()<ZOOM_MAX){
		    framemapa->limpiarFrame();
		    plano.escalarMapa(FACTOR_ZOOM);
		    e_vzoom->insertarTexto(plano.getEscalaStr());
		    SDL_UpdateRect(screen,0,0,0,0);
		}
	    }
	    else if(botonMenosZoom->presionado(event.motion.x,event.motion.y)){
		if(plano.getEscala()>ZOOM_MIN){
		    framemapa->limpiarFrame();
		    plano.escalarMapa(-FACTOR_ZOOM);
		    e_vzoom->insertarTexto(plano.getEscalaStr());
		    SDL_UpdateRect(screen,0,0,0,0);
		}
	    }
	    else if(botonDerecha->presionado(event.motion.x,event.motion.y)){
		framemapa->limpiarFrame();
		plano.despDerecha();
		Punto v(objetivo.getX(),objetivo.getY());
		//v.transformar(framemapa, plano.getEscala(),plano.getDH(),plano.getDV());
		objetivo.dibujar((int)v.getX(),(int)v.getY(), true);
		SDL_UpdateRect(screen,0,0,0,0);
	    }
	    else if(botonIzquierda->presionado(event.motion.x,event.motion.y)){
		framemapa->limpiarFrame();
		plano.despIzquierda();
		SDL_UpdateRect(screen,0,0,0,0);
	    }
	    else if(botonArriba->presionado(event.motion.x,event.motion.y)){
		framemapa->limpiarFrame();
		plano.despArriba();
		SDL_UpdateRect(screen,0,0,0,0);
	    }
	    else if(botonAbajo->presionado(event.motion.x,event.motion.y)){
		framemapa->limpiarFrame();
		plano.despAbajo();
		SDL_UpdateRect(screen,0,0,0,0);
	    }
	    else if(botonCentrar->presionado(event.motion.x,event.motion.y)){
		framemapa->limpiarFrame();
		plano.centrarMapa(screen,framemapa);
		plano.pintarMapa(screen,framemapa,plano.getEscala());
		SDL_UpdateRect(screen,0,0,0,0);
	    }
	    else if(framemapa->getBcerrar()->presionado(event.motion.x,event.motion.y)){
		framemapa->cerrarFrame();
		this->borrar();
	    }	
	    else if(framemapa->getBmaxmin()->presionado(event.motion.x,event.motion.y)){
		this->borrar();
		if(framemapa->getEstado()==MINIMO){
		    frameradar->desactivarFrame();
		    framestado->desactivarFrame();
		    framemapa->maxFrame(MARGEN,MARGEN,SCREEN_W-2*MARGEN,framemapa->getH());
		    plano.pintarMapa(screen,framemapa,plano.getEscala());
		    botonDerecha->recargarBoton();
		    botonIzquierda->recargarBoton();
		    botonAbajo->recargarBoton();
		    botonArriba->recargarBoton();
		    botonCentrar->recargarBoton();
    		    //	Izquierda
		    //Botones Zoom
		    botonMasZoom->cargarBoton(
			    framemapa->getX()+framemapa->getW()-100, 
			    framemapa->getY()+framemapa->getH()+30, 
			    20,
			    20,
			    "+",
			    0xFFA500FF);
		    botonMenosZoom->cargarBoton(
			    framemapa->getX()+framemapa->getW()-50, 
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
		    /* 
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
		    */
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
		    /*botonDerecha->cargarBoton(framemapa->getX()+140, 
			    framemapa->getY()+framemapa->getH()+30, 
			    20,
			    20,
			    ">",
			    0xFFA500FF);*/
		    botonDerecha->recargarBoton();
		    botonIzquierda->recargarBoton();
		    botonAbajo->recargarBoton();
		    botonArriba->recargarBoton();
		    botonCentrar->recargarBoton();
    		    //	Izquierda
		    /*botonIzquierda->cargarBoton(framemapa->getX()+100, 
			    framemapa->getY()+framemapa->getH()+30, 
			    20,
			    20,
			    "<",
			    0xFFA500FF);
			    */

		    //	Arriba
		    /*botonArriba->cargarBoton(framemapa->getX()+120, 
			    framemapa->getY()+framemapa->getH()+10, 
			    20,
			    20,
			    "^",
			    0xFFA500FF);*/
		    //	Abajo
		    /*botonAbajo->cargarBoton(framemapa->getX()+120, 
			    framemapa->getY()+framemapa->getH()+50, 
			    20,
			    20,
			    "V",
			    0xFFA500FF);
			    */
		    //	Centrar
		    /*botonCentrar->cargarBoton(framemapa->getX()+120, 
			    framemapa->getY()+framemapa->getH()+30, 
			    20,
			    20,
			    "C",
			    0xFFA500FF);
			    */
		    // Frame Radar
		    frameradar->cargarFrame(
			    (int)((float)SCREEN_W/10.0*6.0)+2*MARGEN, 
			    SCREEN_H-(int)((float)SCREEN_H/10.0*4.0),
			    (int)((float)SCREEN_W/10.0*2.5)+MARGEN, 
			    (int)((float)SCREEN_H/10.0*4.0),
		    	    "Radar",
			    0xffffff);

		    // Frame Estado
		    framestado->cargarFrame(
			    (int)((float)SCREEN_W/10.0*6.0)+2*MARGEN, 
			    MARGEN,
			    (int)((float)SCREEN_W/10.0*2.5)+MARGEN, 
			    (int)((float)SCREEN_H/10.0*5.5),
			    "Estado",
			    0xffffff);

		}

		SDL_UpdateRect(screen,0,0,0,0);
	    }
	    else if(frameradar->getBmaxmin()->presionado(event.motion.x,event.motion.y)){
		this->borrar();
		if(frameradar->getEstado()==MINIMO){
		    framemapa->desactivarFrame();
		    framestado->desactivarFrame();
		    frameradar->maxFrame(MARGEN,MARGEN,SCREEN_W-2*MARGEN,SCREEN_H-2*MARGEN);
		}else if(frameradar->getEstado()==MAXIMO){
		    frameradar->minFrame(); 
		    framestado->minFrame(); 
		    framemapa->minFrame();
		    plano.pintarMapa(screen,framemapa,plano.getEscala());
		    botonMasZoom->recargarBoton();
		    botonMenosZoom->recargarBoton();
		    botonDerecha->recargarBoton();
		    botonIzquierda->recargarBoton();
		    botonArriba->recargarBoton();
		    botonAbajo->recargarBoton();
		    botonCentrar->recargarBoton();

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
 
		}
		SDL_UpdateRect(screen,0,0,0,0);
	    }
	    else if(framestado->getBmaxmin()->presionado(event.motion.x,event.motion.y)){
		this->borrar();
		if(framestado->getEstado()==MINIMO){
		    framemapa->desactivarFrame();
		    frameradar->desactivarFrame();
		    framestado->maxFrame(MARGEN,MARGEN,SCREEN_W-2*MARGEN,SCREEN_H-2*MARGEN);

		}else if(framestado->getEstado()==MAXIMO){
		    framestado->minFrame(); 
		    frameradar->minFrame(); 
		    framemapa->minFrame();
		    plano.pintarMapa(screen,framemapa,plano.getEscala());
		    botonMasZoom->recargarBoton();
		    botonMenosZoom->recargarBoton();
		    botonDerecha->recargarBoton();
		    botonIzquierda->recargarBoton();
		    botonArriba->recargarBoton();
		    botonAbajo->recargarBoton();
		    botonCentrar->recargarBoton();

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

		}
		SDL_UpdateRect(screen,0,0,0,0);
	    }

	    /*if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)){
	        cout << "boton: izquierdo" << endl;
	    }else if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(2)){
	        cout << "boton: medio" << endl;
	    }else if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3)){
	        cout << "boton: derecho" << endl;
	    }*/
	    break;
 
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

void Pantalla::setAlpha(Frame *frame, Uint8 zona){

    if(!alpha){
	SDL_Rect r,r1,r2,r3,r4,r5;
	r1.x=0;
	r1.y=0;
	r1.w=SCREEN_W;
	r1.h=frame->getY();

	r2.x=0;
	r2.y=r1.h;
	r2.w=frame->getX();
	r2.h=SCREEN_H-r2.y;

	r3.x=frame->getX();
	r3.y=frame->getY()+frame->getH();
	r3.w=frame->getW();
	r3.h=SCREEN_H-r3.y;


	r4.x=frame->getX()+frame->getW();
	r4.y=frame->getY();
	r4.w=SCREEN_W-frame->getX()-frame->getW();
	r4.h=SCREEN_H-r4.y;

	r5.x=frame->getX();
	r5.y=frame->getY();
	r5.w=frame->getW();
	r5.h=frame->getH();

	r.x=0;
	r.y=0;
	r.w=SCREEN_W;
	r.h=SCREEN_H;
	SDL_SetClipRect(screen,&r);

	int i;
	for(i=0;i<20;i++){
	    if(zona&Z_ARRIBA) 
		boxColor(screen, r1.x,r1.y,r1.x+r1.w, r1.y+r1.h, 0x000013);
	    if(zona&Z_IZQUIERDA)
		boxColor(screen, r2.x,r2.y,r2.x+r2.w, r2.y+r2.h, 0x000013);
	    if(zona&Z_ABAJO) 
		boxColor(screen, r3.x,r3.y,r.x+r3.w, r3.y+r3.h, 0x000013);
	    if(zona&Z_DERECHA) 
		boxColor(screen, r4.x,r4.y,r4.x+r4.w, r4.y+r4.h, 0x000013);
	    
	    if(zona&Z_CENTRO) 
		boxColor(screen, r5.x,r5.y,r5.x+r5.w, r5.y+r5.h, 0x000013);
	    SDL_UpdateRect(screen,0,0,0,0);
	    usleep(1000);
	}
	alpha=true;
    }
}

bool Pantalla::salir()
{
	return sdl_quit;
}
