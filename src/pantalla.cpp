#include "pantalla.h"
#include "constantes.h"
#include "boton.h"
#include "mapa.h"
#include "etiqueta.h"
#include "tabla.h"
#include "objetivo.h"
#include "radar.h"
#include <SDL/SDL_thread.h>
#include <sstream>
#include "clientecapa_alta.h"
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
extern ClienteCapaAlta clienteCapaAlta;
extern Radar *radar;
extern SDL_mutex *mutexSincRadar;
extern SDL_cond *condSincRadar;
extern bool pauseRadar;
extern Tabla tcampos;
Pantalla::Pantalla(SDL_Surface *screen) 
{
    this->screen=screen;
//    Uint8 video_bpp;
//    Uint32 videoflags;
//    videoflags = SDL_SWSURFACE | SDL_SRCALPHA ;
    h_screen=SCREEN_H;
    v_screen=SCREEN_W;
    sdl_quit=false;
    alpha=false;
    info = SDL_GetVideoInfo();
/*    if ( info->vfmt->BitsPerPixel > 8 ) {
	video_bpp = info->vfmt->BitsPerPixel;
    } else {
	video_bpp = 16;
    }
    screen=SDL_SetVideoMode(v_screen, h_screen, video_bpp, videoflags);
//SDL_DOUBLEBUF|SDL_SWSURFACE);	
    SDL_SetAlpha(screen, SDL_SRCALPHA, 0);
    SDL_FillRect( screen, 0, 0x000000);
    SDL_UpdateRect(screen,0,0,0,0);
*/
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
    SDL_Delay(100);//eliminar espera activa, reducir el consumo de CPU
    while ( SDL_PollEvent( &event ) ) 
    
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
	    break;
 
	case SDL_QUIT:
	    //Boton de salir
	    sdl_quit = true;
	    break;
 
	case SDL_MOUSEBUTTONDOWN:
	    cout << "click" << endl;
	    cout << "x:" << event.motion.x << " y:" << event.motion.y <<  endl;
	    Punto p;
	    p.cplano(event.motion.x, event.motion.y,plano.getEscala(),plano.getOX(),plano.getOY());
	    if(objetivo.preguntado()){
		int respuesta=objetivo.respuesta(event.motion.x,event.motion.y);
		switch(respuesta){
		    case SIN_RESPUESTA:
			break;
		    case RESPUESTA_SI:
			objetivo.activar();
			objetivo.nopreguntar();
			framemapa->limpiarFrame(false);
			plano.pintarMapa(screen,framemapa,plano.getEscala());
			objetivo.dibujar();
			objetivo.store();//guardarlo
			clienteCapaAlta.Send("@ "+objetivo.toString());
			cout << "objetivo:" <<objetivo.toString() << endl;
			break;
		    case RESPUESTA_NO:
			objetivo.nopreguntar();
			framemapa->limpiarFrame(false);
			plano.pintarMapa(screen,framemapa,plano.getEscala());
			if(objetivo.getFijado())objetivo.load();//cargarlo
			objetivo.dibujar();
			break;	    
		}
	    }
	    else if(!objetivo.preguntado()&&framemapa->Presionado(event.motion.x,event.motion.y)){
		
		if(!objetivo.preguntado())objetivo.setObjetivo(framemapa, &plano,p.getX(),p.getY());		
		Polilinea contorno=
		    plano.getCapa("CapaContorn")->getPolilinea()->front();
		if(objetivo.interior(contorno)){
		    
		    vector<Polilinea> *obstaculos=
			plano.getCapa("CapaObstacles")->getPolilinea();

		    objetivo.setValido(true);
		    vector<Polilinea>::iterator i_obstaculo;
		    for(i_obstaculo=obstaculos->begin();
			    i_obstaculo!=obstaculos->end();
			    i_obstaculo++)
		    {
			if(objetivo.interior((*i_obstaculo))){
			    objetivo.setValido(false);
			    break;
			}
		    }

		    string zona="no id";
		    vector<Polilinea> *habitaciones=
			plano.getCapa("CapaHabitacions")->getPolilinea();
		    vector<Polilinea>::iterator i_habitacion;
		    for(i_habitacion=habitaciones->begin();
			    i_habitacion!=habitaciones->end();
			    i_habitacion++)
		    {
			if(objetivo.interior((*i_habitacion))){
			    zona=(*i_habitacion).getHabitacion();
			    break;
			}
		    }
		    
		    string titulo,
			   pos;
		    bool pos_correcta;
		    Uint32 color_etiq,
			   sincolor=0x00000000,
			   color_valor=0x00FF00FF;
			    
		    if(!objetivo.getValido()){
			cout << "error: obstaculo" << endl;
			titulo = " Obstaculo! ";//msg
			ostringstream buffer;//msg
			buffer << (int)p.getX()<< "," << (int)p.getY();//msg
			pos=buffer.str();//msg
			//this->setAlpha(framemapa,Z_CENTRO);//efecto alpha
			color_etiq=0xFF0000FF;//color
		    }else{
			titulo=" Objetivo ";
			ostringstream buffer;//msg
			buffer << (int)p.getX()<< "," << (int)p.getY();//msg
			pos=buffer.str();//msg
			color_etiq=0x5757FFFF;//color
		    }
		    if(!objetivo.preguntado()){
			objetivo.dibujar();
			if(objetivo.getValido())objetivo.preguntar();
		    }

		    //Posicion de la etiqueta pregunta
		    int x1=event.motion.x-50;
		    int x2=x1+titulo.size()*SIZE_C+10;
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
		    
		    //Etiquetas
		    x1=(int)((framemapa->getW()*0.5+framemapa->getX())-(10*SIZE_C)*0.5)-10;		    
		    y1=(int)(framemapa->getY()+framemapa->getH()+5);
		    //Limpiar Zona Etiquetas
		    SDL_Rect r;
		    r.x=x1;
		    r.y=y1;
		    r.w=SIZE_C*15;
		    r.h=SIZE_C*5*2;
		    extern SDL_mutex *semVideo;
		    SDL_mutexP(semVideo);
		    if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
		    SDL_SetClipRect(screen,&r);
		    boxColor(screen,r.x,r.y,r.x+r.w,r.y+r.h,0x000000FF);
		    if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
		    SDL_mutexV(semVideo);

		    Etiqueta *info;
		    info=new Etiqueta(screen);
		    //titulo
		    info->cargarEtiqueta(
			    x1,
			    y1,
			    titulo.size()*SIZE_C,
			    SIZE_C*2,
			    (char*)titulo.c_str(),
			    color_etiq,
			    color_etiq,
			    0x00000043);
		    //Pos
		    titulo="Pos:";
		    y1+=SIZE_C*2;
		    info->cargarEtiqueta(
			    x1,
			    y1,
			    titulo.size()*SIZE_C,
			    SIZE_C*2,
			    (char*)titulo.c_str(),
			    color_etiq,
			    sincolor,
			    0x00000043);
		    y1+=SIZE_C*2;
		    info->cargarEtiqueta(
			    x1,
			    y1,
			    pos.size()*SIZE_C,
			    SIZE_C*2,
			    (char*)pos.c_str(),
			    color_valor,
			    sincolor,
			    0x00000043);
		    //Zona
		    titulo="Zona:";
		    y1+=SIZE_C*2;
		    info->cargarEtiqueta(
			    x1,
			    y1,
			    titulo.size()*SIZE_C,
			    SIZE_C*2,
			    (char*)titulo.c_str(),
			    color_etiq,
			    sincolor,
			    0x00000043);
		    y1+=SIZE_C*2;
		    info->cargarEtiqueta(
			    x1,
			    y1,
			    zona.size()*SIZE_C,
			    SIZE_C*2,
			    (char*)zona.c_str(),
			    color_valor,
			    sincolor,
			    0x00000043);


		    cout << "\tpx:" << p.getX() << ", py:" << p.getY() << endl;
		}
	    }
	    
	    if(botonMasZoom->presionado(event.motion.x,event.motion.y)){
	        if(plano.getEscala()<ZOOM_MAX){
		    framemapa->limpiarFrame(false);
		    plano.escalarMapa(FACTOR_ZOOM);
		    if(objetivo.getFijado()){
			objetivo.load();
			objetivo.dibujar();
		    }
		    if(objetivo.preguntado())objetivo.nopreguntar();
		    e_vzoom->insertarTexto(plano.getEscalaStr());
		    //SDL_UpdateRect(screen,0,0,0,0);
		    framemapa->refrescarFrame();
		}
	    }
	    else if(botonMenosZoom->presionado(event.motion.x,event.motion.y)){
		if(plano.getEscala()>ZOOM_MIN){
		    framemapa->limpiarFrame(false);
		    plano.escalarMapa(-FACTOR_ZOOM);
		    e_vzoom->insertarTexto(plano.getEscalaStr());
		    if(objetivo.getFijado()){
			objetivo.load();
			objetivo.dibujar();
		    }
		    if(objetivo.preguntado())objetivo.nopreguntar();
		    //SDL_UpdateRect(screen,0,0,0,0);
		    framemapa->refrescarFrame();
		}
	    }
	    else if(botonDerecha->presionado(event.motion.x,event.motion.y)){
		framemapa->limpiarFrame(false);
		plano.despDerecha();
		if(objetivo.getFijado()){
		    objetivo.load();
		    objetivo.dibujar();
		}
		if(objetivo.preguntado())objetivo.nopreguntar();
		//SDL_UpdateRect(screen,0,0,0,0);
		framemapa->refrescarFrame();
	    }
	    else if(botonIzquierda->presionado(event.motion.x,event.motion.y)){
		framemapa->limpiarFrame(false);
		plano.despIzquierda();
		if(objetivo.getFijado()){
		    objetivo.load();
		    objetivo.dibujar();
		}
		if(objetivo.preguntado())objetivo.nopreguntar();
		//SDL_UpdateRect(screen,0,0,0,0);
		framemapa->refrescarFrame();
	    }
	    else if(botonArriba->presionado(event.motion.x,event.motion.y)){
		framemapa->limpiarFrame(false);
		plano.despArriba();
		if(objetivo.getFijado()){
		    objetivo.load();
		    objetivo.dibujar();
		}
		if(objetivo.preguntado())objetivo.nopreguntar();
		//SDL_UpdateRect(screen,0,0,0,0);
		framemapa->refrescarFrame();
	    }
	    else if(botonAbajo->presionado(event.motion.x,event.motion.y)){
		framemapa->limpiarFrame(false);
		plano.despAbajo();
		if(objetivo.getFijado()){
		    objetivo.load();
		    objetivo.dibujar();
		}
		if(objetivo.preguntado())objetivo.nopreguntar();
		//SDL_UpdateRect(screen,0,0,0,0);
		framemapa->refrescarFrame();
	    }
	    else if(botonCentrar->presionado(event.motion.x,event.motion.y)){
		framemapa->limpiarFrame(false);
		plano.centrarMapa();
		plano.pintarMapa(screen,framemapa,plano.getEscala());
		if(objetivo.getFijado()){
		    objetivo.load();
		    objetivo.dibujar();
		}
		if(objetivo.preguntado())objetivo.nopreguntar();
		//SDL_UpdateRect(screen,0,0,0,0);
		framemapa->refrescarFrame();
	    }
	    else if(framemapa->getBcerrar()->presionado(event.motion.x,event.motion.y)){
		framemapa->cerrarFrame();
		this->borrar();
	    }	
	    else if(framemapa->getBmaxmin()->presionado(event.motion.x,event.motion.y)){
		this->borrar();
		if(framemapa->getEstado()==MINIMO){
		    
		    SDL_mutexP(mutexSincRadar);
		    pauseRadar=true;
		    SDL_mutexV(mutexSincRadar);

		    frameradar->desactivarFrame();
		    framestado->desactivarFrame();
		    framemapa->maxFrame(MARGEN,MARGEN,SCREEN_W-2*MARGEN,framemapa->getH());
		    plano.pintarMapa(screen,framemapa,plano.getEscala());
		    if(objetivo.getFijado()){
			objetivo.load();
			objetivo.dibujar();
		    }
		    if(objetivo.preguntado())objetivo.nopreguntar();

		    botonDerecha->recargarBoton();
		    botonIzquierda->recargarBoton();
		    botonAbajo->recargarBoton();
		    botonArriba->recargarBoton();
		    botonCentrar->recargarBoton();
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
		}else{ 
		    this->minimizar();
		    SDL_mutexP(mutexSincRadar);
		    pauseRadar=false;
		    SDL_mutexV(mutexSincRadar);
		    SDL_CondSignal(condSincRadar);
		    
		}

		//SDL_UpdateRect(screen,0,0,0,0);
	    }
	    else if(frameradar->getBmaxmin()->presionado(event.motion.x,event.motion.y)){
		this->borrar();
		if(frameradar->getEstado()==MINIMO){
		    framemapa->desactivarFrame();
		    framestado->desactivarFrame();
		    frameradar->maxFrame(MARGEN,MARGEN,SCREEN_W-2*MARGEN,SCREEN_H-2*MARGEN);

		    //desactivar botones de zoom y desplazamiento
		    botonDerecha->desactivar();
		    botonIzquierda->desactivar();
		    botonAbajo->desactivar();
		    botonArriba->desactivar();
		    botonCentrar->desactivar();
		    botonMasZoom->desactivar();
		    botonMenosZoom->desactivar();

		    radar->recargar(false);
		}else if(frameradar->getEstado()==MAXIMO){
		    this->minimizar();
		    radar->recargar(false);
		}
		//SDL_UpdateRect(screen,0,0,0,0);
	    }
	    else if(framestado->getBmaxmin()->presionado(event.motion.x,event.motion.y)){
		this->borrar();
		if(framestado->getEstado()==MINIMO){
		    
		    SDL_mutexP(mutexSincRadar);
		    pauseRadar=true;
		    SDL_mutexV(mutexSincRadar);
		    
		    frameradar->desactivarFrame();
		    framestado->maxFrame(MARGEN,MARGEN,SCREEN_W-2*MARGEN,SCREEN_H-2*MARGEN);
		    framemapa->desactivarFrame();
		    //desactivar botones de zoom y desplazamiento
		    botonDerecha->desactivar();
		    botonIzquierda->desactivar();
		    botonAbajo->desactivar();
		    botonArriba->desactivar();
		    botonCentrar->desactivar();
		    botonMasZoom->desactivar();
		    botonMenosZoom->desactivar();

		    tcampos.recargar(framestado);
		}else if(framestado->getEstado()==MAXIMO){
		    this->minimizar();
		    SDL_mutexP(mutexSincRadar);
		    pauseRadar=false;
		    SDL_mutexV(mutexSincRadar);
		    SDL_CondSignal(condSincRadar);
		    
		}
	    }
	    tcampos.handle( event.motion.x, event.motion.y);
		



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
    if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
    SDL_FillRect( screen, 0, 0x000000);
    if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
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
	extern SDL_mutex *semVideo;
	SDL_mutexP(semVideo);
	SDL_SetClipRect(screen,&r);

	int i;
	for(i=0;i<20;i++){
	    if(zona&Z_ARRIBA){ 
		if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
		boxColor(screen, r1.x,r1.y,r1.x+r1.w, r1.y+r1.h, 0x000013);
		if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
	    }
	    if(zona&Z_IZQUIERDA){
		if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
		boxColor(screen, r2.x,r2.y,r2.x+r2.w, r2.y+r2.h, 0x000013);
		if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
	    }
	    if(zona&Z_ABAJO) {
		if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
		boxColor(screen, r3.x,r3.y,r.x+r3.w, r3.y+r3.h, 0x000013);
		if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
	    }
	    if(zona&Z_DERECHA) {
		if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
		boxColor(screen, r4.x,r4.y,r4.x+r4.w, r4.y+r4.h, 0x000013);
		if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
	    }
	    
	    if(zona&Z_CENTRO) {
		if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
		boxColor(screen, r5.x,r5.y,r5.x+r5.w, r5.y+r5.h, 0x000013);
		if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
		SDL_UpdateRect(screen, r5.x,r5.y,r5.w,r5.h);
	    }
	    //SDL_UpdateRect(screen,0,0,0,0);
	    usleep(1000);
	}
	SDL_mutexV(semVideo);
	//alpha=true;
    }
}

bool Pantalla::salir()
{
	return sdl_quit;
}

void Pantalla::minimizar(){
    frameradar->minFrame(); 
    framestado->minFrame(); 
    framemapa->minFrame(); 
    plano.pintarMapa(screen,framemapa,plano.getEscala());
    if(objetivo.getFijado()){
	objetivo.load();
	objetivo.dibujar();
    }
    if(objetivo.preguntado())objetivo.nopreguntar();

    botonDerecha->recargarBoton();
    botonIzquierda->recargarBoton();
    botonAbajo->recargarBoton();
    botonArriba->recargarBoton();
    botonCentrar->recargarBoton();

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
    tcampos.recargar(framestado);
}

