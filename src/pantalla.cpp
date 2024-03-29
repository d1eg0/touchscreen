/**
 *       @file  pantalla.cpp
 *
 *     @author  Diego García , kobydiego@gmail.com
 *
 *   @internal
 *     Company  Universitat de les Illes Balears
 *   Copyright  Copyright (c) 2009, Diego García
 *
 *
 *  This file is part of TouchScreenGUI.
 *  TouchScreenGUI is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  TouchScreenGUI is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TouchScreenGUI; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  http://www.gnu.org/copyleft/gpl.html
 *
 * =====================================================================================
 */

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
#include <iostream>
#include "clientecapa_alta.h"
#include "silla.h"
#include "selector.h"
extern Boton *botonMasZoom, 
       *botonMenosZoom,
       *botonAjustarZoom;
extern Boton *botonDerecha,
       *botonIzquierda,
       *botonArriba,
       *botonAbajo,
       *botonCentrar,
       *botonSelector,
       *botonOnoff;
extern Mapa plano;
extern Frame *framemapa,
       *frameradar,
       *framestado,
       *frameselector;
extern Etiqueta *e_zoom;//,*e_vzoom;
extern Objetivo objetivo;
extern ClienteCapaAlta clienteCapaAlta;
extern Radar *radar;
extern SDL_mutex *mutexSincRadar;
extern SDL_cond *condSincRadar;
extern bool pauseRadar;
extern Tabla tcampos;
extern Silla *silla;
extern Selector *selector;

Pantalla::Pantalla(SDL_Surface *screen) 
{
    this->screen=screen;
    //    Uint8 video_bpp;
    //    Uint32 videoflags;
    //    videoflags = SDL_SWSURFACE | SDL_SRCALPHA ;
    h_screen=SCREEN_H;
    v_screen=SCREEN_W;
    sdl_quit=false;
    //alpha=false;
    handle=true;
    info = SDL_GetVideoInfo();
}

Pantalla::~Pantalla() 
{
    SDL_Quit();
}

void Pantalla::hideCursor(){
    SDL_Cursor *cursor;
    Uint8 data[2]={0x00, 0x00};
    Uint8 mask[2]={0x00, 0x00};
    cursor=SDL_CreateCursor(data,mask,2,1,0,0);
    SDL_SetCursor(cursor);
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

		if(!handle)return;
		int mouse_x=event.motion.x;
		int mouse_y=event.motion.y;
		cout << "x:" << mouse_x << " y:" << mouse_y <<  endl;
		Punto p;
		p.cplano(mouse_x, mouse_y,framemapa,plano.getDH(),plano.getDV(),plano.getEscala());
		if(objetivo.preguntado()){
		    int respuesta=objetivo.respuesta(mouse_x,mouse_y);
		    string dataObjetivo;
		    switch(respuesta){
			case SIN_RESPUESTA:
			    break;
			case RESPUESTA_SI:
			    objetivo.activar();
			    objetivo.nopreguntar();
			    framemapa->limpiarFrame(false);
			    plano.pintarMapa(screen,plano.getEscala());
			    objetivo.dibujar();
			    objetivo.store();//guardarlo
			    dataObjetivo=CABECERA_OBJETIVO+objetivo.toString()+"\r\n";
			    clienteCapaAlta.Send(dataObjetivo);
			    //cout << "objetivo:" <<objetivo.toString() << endl << "paquete: "<< dataObjetivo << endl;
			    break;
			case RESPUESTA_NO:
			    objetivo.nopreguntar();
			    framemapa->limpiarFrame(false);
			    plano.pintarMapa(screen,plano.getEscala());
			    if(objetivo.getFijado())objetivo.load();//cargarlo
			    objetivo.dibujar();
			    break;	    
		    }
		}
		else if(!objetivo.preguntado()&&framemapa->presionado(mouse_x,mouse_y)){
		    objetivo.setObjetivo(framemapa, &plano,p.getX(),p.getY());		
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
			    cerr << "[E]: click sobre obstaculo" << endl;
			    titulo = " Obstaculo! ";//msg
			    ostringstream buffer;//msg
			    buffer << (int)p.getX()<< "," << (int)p.getY();//msg
			    pos=buffer.str();//msg
			    //this->setAlpha(framemapa,Z_CENTRO);//efecto alpha
			    color_etiq=0xFF0000FF;//color
			}else{
			    titulo="  Objetivo  ";
			    ostringstream buffer;//msg
			    char possub[16];
			    sprintf(possub,"%4.3f %4.3f",p.getX(),p.getY());
			    buffer << possub;//msg
			    pos=buffer.str();//msg
			    color_etiq=0x5757FFFF;//color
			}
			if(!objetivo.preguntado()){
			    objetivo.dibujar();
			    if(objetivo.getValido())objetivo.preguntar();
			}

			//Posicion de la etiqueta pregunta
			int x1=mouse_x-50;
			int x2=x1+titulo.size()*SIZE_C+10;
			int y1=mouse_y-50;
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
			SDL_UpdateRect(screen,r.x,r.y,r.w,r.h);
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
			titulo="Posicion:";
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
		    }else{
			cout << " Fuera " << endl;
			int x1,y1;
			string titulo=" Pto. Fuera ",
			       pos;
			bool pos_correcta;
			Uint32 color_etiq,
			       sincolor=0x00000000,
			       color_valor=0x00FF00FF;

			color_etiq=0xFF0000FF;//color
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
			SDL_UpdateRect(screen,r.x,r.y,r.w,r.h);
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

		    }
		}	    
		else if(botonMasZoom->presionado(mouse_x,mouse_y)){
		    if(plano.getEscala()<ZOOM_MAX){
			framemapa->limpiarFrame(false);
			plano.escalarMapa(FACTOR_ZOOM);
			silla->dibujar();
			if(objetivo.getFijado()){
			    objetivo.load();
			    objetivo.dibujar();
			}
			if(objetivo.preguntado())objetivo.nopreguntar();
			//e_vzoom->insertarTexto(plano.getEscalaStr());
			framemapa->refrescarFrame();
		    }
		}
		else if(botonMenosZoom->presionado(mouse_x,mouse_y)){
		    if(plano.getEscala()>ZOOM_MIN){
			framemapa->limpiarFrame(false);
			plano.escalarMapa(-FACTOR_ZOOM);
			silla->dibujar();
			//e_vzoom->insertarTexto(plano.getEscalaStr());
			if(objetivo.getFijado()){
			    objetivo.load();
			    objetivo.dibujar();
			}
			if(objetivo.preguntado())objetivo.nopreguntar();
			framemapa->refrescarFrame();
		    }
		}
		else if(botonAjustarZoom->presionado(mouse_x,mouse_y)){
		    framemapa->limpiarFrame(false);
		    plano.centrarMapa();
		    plano.calcularZoom();
		    plano.pintarMapa(screen,plano.getEscala());
		    silla->dibujar();
		    if(objetivo.getFijado()){
			objetivo.load();
			objetivo.dibujar();
		    }
		    if(objetivo.preguntado())objetivo.nopreguntar();
		    //e_vzoom->insertarTexto(plano.getEscalaStr());
		    framemapa->refrescarFrame();
		}
		else if(botonDerecha->presionado(mouse_x,mouse_y)){
		    framemapa->limpiarFrame(false);
		    plano.despDerecha();
		    silla->dibujar();
		    if(objetivo.getFijado()){
			objetivo.load();
			objetivo.dibujar();
		    }
		    if(objetivo.preguntado())objetivo.nopreguntar();
		    framemapa->refrescarFrame();
		}
		else if(botonIzquierda->presionado(mouse_x,mouse_y)){
		    framemapa->limpiarFrame(false);
		    plano.despIzquierda();
		    silla->dibujar();
		    if(objetivo.getFijado()){
			objetivo.load();
			objetivo.dibujar();
		    }
		    if(objetivo.preguntado())objetivo.nopreguntar();
		    framemapa->refrescarFrame();
		}
		else if(botonArriba->presionado(mouse_x,mouse_y)){
		    framemapa->limpiarFrame(false);
		    plano.despArriba();
		    silla->dibujar();
		    if(objetivo.getFijado()){
			objetivo.load();
			objetivo.dibujar();
		    }
		    if(objetivo.preguntado())objetivo.nopreguntar();
		    framemapa->refrescarFrame();
		}
		else if(botonAbajo->presionado(mouse_x,mouse_y)){
		    framemapa->limpiarFrame(false);
		    plano.despAbajo();
		    silla->dibujar();
		    if(objetivo.getFijado()){
			objetivo.load();
			objetivo.dibujar();
		    }
		    if(objetivo.preguntado())objetivo.nopreguntar();
		    framemapa->refrescarFrame();
		}
		else if(botonCentrar->presionado(mouse_x,mouse_y)){
		    framemapa->limpiarFrame(false);
		    plano.centrarMapa();
		    plano.pintarMapa(screen,plano.getEscala());
		    silla->dibujar();
		    if(objetivo.getFijado()){
			objetivo.load();
			objetivo.dibujar();
		    }
		    if(objetivo.preguntado())objetivo.nopreguntar();
		    framemapa->refrescarFrame();
		}
		else if(botonSelector->presionado(mouse_x,mouse_y)){
		    if(frameselector->getEstado()==CERRADO){
			selector=new Selector(screen);
			//selector->buscarW("/media/disk/","dxf");
			selector->buscarW("/mnt/usb/USB1/","dxf");
		    }
		}
		else if(framemapa->getBmaxmin()->presionado(mouse_x,mouse_y)){
		    if(framemapa->getEstado()==MINIMO){
			SDL_mutexP(mutexSincRadar);
			pauseRadar=true;
			SDL_mutexV(mutexSincRadar);
			this->borrar();

			frameradar->desactivarFrame();
			framestado->desactivarFrame();
			framemapa->maxFrame(MARGENH,MARGENV,SCREEN_W-2*MARGENH,framemapa->getH());
			plano.pintarMapa(screen,plano.getEscala());
			silla->dibujar();
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
				0xFFA500FF,
				COLOR_BORDER_BOTON);
			botonMenosZoom->cargarBoton(
				framemapa->getX()+framemapa->getW()-50, 
				framemapa->getY()+framemapa->getH()+30, 
				20,
				20,
				"-",
				0xFFA500FF,
				COLOR_BORDER_BOTON);
			botonAjustarZoom->cargarBoton(
				framemapa->getX()+framemapa->getW()-75, 
				framemapa->getY()+framemapa->getH()+30, 
				20,
				20,
				"[]",
				0xFFA500FF,
				COLOR_BORDER_BOTON);


			//Etiqueta Zoom
			e_zoom->cargarEtiqueta(framemapa->getX()+framemapa->getW()-100,	    
				framemapa->getY()+framemapa->getH()+10,
				70,
				20,
				"Zoom",
				COLOR_FUENTE,
				0x000000FF,
				COLOR_BG);

			/*e_vzoom->cargarEtiqueta(framemapa->getX()+framemapa->getW()-100,
			  framemapa->getY()+framemapa->getH()+50,
			  70,
			  20,
			  plano.getEscalaStr(),
			  0xFFA500FF,
			  0xFFA500FF,
			  COLOR_BG);
			  */
		    }else{ 
			this->borrar();
			this->minimizar();
			SDL_mutexP(mutexSincRadar);
			pauseRadar=false;
			SDL_mutexV(mutexSincRadar);
			SDL_CondSignal(condSincRadar);

		    }
		}
		else if(frameradar->getBmaxmin()->presionado(mouse_x,mouse_y)){
		    this->borrar();
		    if(frameradar->getEstado()==MINIMO){
			framemapa->desactivarFrame();
			framestado->desactivarFrame();
			frameradar->maxFrame(MARGENH, MARGENV, SCREEN_W-2*MARGENH, SCREEN_H-2*MARGENV);

			//desactivar botones de zoom y desplazamiento
			botonDerecha->desactivar();
			botonIzquierda->desactivar();
			botonAbajo->desactivar();
			botonArriba->desactivar();
			botonCentrar->desactivar();
			botonAjustarZoom->desactivar();
			botonMasZoom->desactivar();
			botonMenosZoom->desactivar();

			radar->recargar(false);
		    }else if(frameradar->getEstado()==MAXIMO){
			this->minimizar();
			radar->recargar(false);
		    }
		    //SDL_UpdateRect(screen,0,0,0,0);
		}
		else if(framestado->getBmaxmin()->presionado(mouse_x,mouse_y)){
		    if(framestado->getEstado()==MINIMO){

			SDL_mutexP(mutexSincRadar);
			pauseRadar=true;
			SDL_mutexV(mutexSincRadar);
			this->borrar();

			frameradar->desactivarFrame();
			framestado->maxFrame(MARGENH,MARGENV,SCREEN_W-2*MARGENH,SCREEN_H-2*MARGENV);
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
			this->borrar();
			this->minimizar();
			SDL_mutexP(mutexSincRadar);
			pauseRadar=false;
			SDL_mutexV(mutexSincRadar);
			SDL_CondSignal(condSincRadar);

		    }
		}
		else if(frameselector->getEstado()!=CERRADO
			&&frameselector->presionado(mouse_x,mouse_y)){
		    if(selector->handle(mouse_x,mouse_y)){
			clienteCapaAlta.enviarPlano(plano.getPath());
		    }

		}
		else if(framestado->presionado(mouse_x,mouse_y)){
		    tcampos.handle( mouse_x, mouse_y);
		}else if(botonOnoff->presionado(mouse_x,mouse_y)){
		    silla->toogleStatus();
		    stringstream buf;
		    buf << CABECERA_STATUS << " " << silla->getStatus() << "\r\n";
		    cout << buf.str() << endl;
		    clienteCapaAlta.enviar(buf.str());
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
    extern SDL_mutex *semVideo;
    SDL_mutexP(semVideo);
    if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
    SDL_FreeSurface(screen);
    SDL_SetClipRect(screen,&r);
    SDL_FillRect( screen, 0, COLOR_BG);
    if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
    SDL_UpdateRect(screen,0,0,0,0);
    SDL_mutexV(semVideo);
}

void Pantalla::setAlpha(Frame *frame, Uint8 zona){

    if(!(zona&Z_TOTAL)){
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
	int i;
	for(i=0;i<20;i++){
	    if(zona&Z_ARRIBA){ 
		SDL_mutexP(semVideo);
		if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
		SDL_SetClipRect(screen,&r1);
		boxColor(screen, r1.x,r1.y,r1.x+r1.w, r1.y+r1.h, 0x000013);
		if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
		SDL_mutexV(semVideo);
	    }
	    if(zona&Z_IZQUIERDA){
		SDL_mutexP(semVideo);
		if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
		SDL_SetClipRect(screen,&r2);
		boxColor(screen, r2.x,r2.y,r2.x+r2.w, r2.y+r2.h, 0x000013);
		if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
		SDL_mutexV(semVideo);
	    }
	    if(zona&Z_ABAJO) {
		SDL_mutexP(semVideo);
		if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
		boxColor(screen, r3.x,r3.y,r.x+r3.w, r3.y+r3.h, 0x000013);
		if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
		SDL_mutexV(semVideo);
	    }
	    if(zona&Z_DERECHA) {
		SDL_mutexP(semVideo);
		if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
		SDL_SetClipRect(screen,&r4);
		boxColor(screen, r4.x,r4.y,r4.x+r4.w, r4.y+r4.h, 0x000013);
		if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
		SDL_mutexV(semVideo);
	    }

	    if(zona&Z_CENTRO) {
		SDL_mutexP(semVideo);
		if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
		SDL_SetClipRect(screen,&r5);
		boxColor(screen, r5.x,r5.y,r5.x+r5.w, r5.y+r5.h, 0x000013);
		if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
		SDL_UpdateRect(screen, r5.x,r5.y,r5.w,r5.h);
		SDL_mutexV(semVideo);
	    }
	    SDL_Delay(10);
	}
    }else{
	SDL_Rect r;
	r.x=0;
	r.y=0;
	r.w=SCREEN_W;
	r.h=SCREEN_H;
	int i;
	extern SDL_mutex *semVideo;
	for(i=0;i<20;i++){
	    SDL_mutexP(semVideo);
	    if(SDL_MUSTLOCK(screen))SDL_LockSurface(screen);
	    SDL_SetClipRect(screen,&r);
	    boxColor(screen, r.x,r.y,r.x+r.w, r.y+r.h, 0x000013);
	    if(SDL_MUSTLOCK(screen))SDL_UnlockSurface(screen);
	    SDL_UpdateRect(screen, r.x,r.y,r.w,r.h);
	    SDL_mutexV(semVideo);
	    SDL_Delay(10);

	}

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
    frameselector->desactivarFrame(); 
    plano.centrarMapa();
    plano.calcularZoom();
    plano.pintarMapa(screen,plano.getEscala());
    silla->dibujar();
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
    botonSelector->recargarBoton();
    botonOnoff->recargarBoton();

    //Botones Zoom
    botonMasZoom->cargarBoton(framemapa->getX()+framemapa->getW()-100, 
	    framemapa->getY()+framemapa->getH()+30, 
	    20,
	    20,
	    "+",
	    0xFFA500FF,
	    COLOR_BORDER_BOTON);
    botonMenosZoom->cargarBoton(framemapa->getX()+framemapa->getW()-50, 
	    framemapa->getY()+framemapa->getH()+30, 
	    20,
	    20,
	    "-",
	    0xFFA500FF,
	    COLOR_BORDER_BOTON);
    botonAjustarZoom->cargarBoton(
	    framemapa->getX()+framemapa->getW()-75, 
	    framemapa->getY()+framemapa->getH()+30, 
	    20,
	    20,
	    "[]",
	    0xFFA500FF,
	    COLOR_BORDER_BOTON);


    //Etiqueta Zoom
    e_zoom->cargarEtiqueta(framemapa->getX()+framemapa->getW()-100,	    
	    framemapa->getY()+framemapa->getH()+10,
	    70,
	    20,
	    "Zoom",
	    COLOR_FUENTE,
	    0x000000FF,
	    COLOR_BG);
    /*e_vzoom->cargarEtiqueta(framemapa->getX()+framemapa->getW()-100,
      framemapa->getY()+framemapa->getH()+50,
      70,
      20,
      plano.getEscalaStr(),
      0xFFA500FF,
      0xFFA500FF,
      COLOR_BG);*/
    tcampos.recargar(framestado);
}
void Pantalla::mapaOff(){
    framemapa->desactivarFrame();
    botonMenosZoom->deshabilitar();
    botonMasZoom->deshabilitar();
    botonDerecha->deshabilitar();
    botonIzquierda->deshabilitar();
    botonArriba->deshabilitar();
    botonAbajo->deshabilitar();
    botonCentrar->deshabilitar();
}

void Pantalla::setHandle(bool handle){
    this->handle=handle;
}

