#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <dxflib/dl_dxf.h>
#include "pantalla.h"
#include "boton.h"
#include "etiqueta.h"
#include "frame.h"
#include "constantes.h"
#include "dxfparser.h"
#include "mapa.h"
#include "campo.h"
#include "objetivo.h"
#include "clientecapa_alta.h"
#include "clientecapa_baja.h"
#include "gestorestado.h"
#include "gestorcamino.h"
#include "radar.h"
#include "tabla.h"
#include "silla.h"
#include "selector.h"
#include <pthread.h>
using namespace std;
SDL_Surface *surfacePrincipal;
Pantalla *pantalla;
//Botones
//  Zoom
Boton *botonMasZoom;
Boton *botonMenosZoom;
Boton *botonAjustarZoom;
//  Desplazar
Boton *botonArriba,
      *botonAbajo,
      *botonDerecha,
      *botonIzquierda,
      *botonCentrar,
      *botonSelector,
      *botonOnoff;
// Frames
Frame *framemapa,
      *frameradar,
      *framestado,
      *frameselector;

// Etiquetas
Etiqueta *e_zoom,
	 *e_vzoom;

Mapa  plano;
Objetivo objetivo;
Radar *radar;
Silla *silla;
Selector *selector;
// Mutex
//  Sincroniza el hilo gestor camino con la recepcion de datos
SDL_mutex *mutexCapaAlta;
SDL_cond *caminoNuevoCond;
//  Sincroniza el hilo gestor camino con la recepcion de datos
SDL_mutex *mutexCapaBaja;
SDL_cond *sensorNuevoCond;
//  Sincroniza el radar
SDL_mutex *mutexSincRadar;
SDL_cond *condSincRadar;
bool pauseRadar;
//  Video
SDL_mutex *semVideo;
//  Obstaculos
SDL_mutex *mutexObstaculo;
//  Silla
SDL_mutex *mutexRot;
// Datos capa baja

//Campos de estado
Campo *cconex,
      *cgrid,
      *cdobstaculo,
      *cprueba,
      *cvelocidad;
//Tabla de campos
Tabla tcampos;
// Comunicacion
ClienteCapaAlta clienteCapaAlta; //Plano y coordenadas
ClienteCapaBaja	clienteCapaBaja; //Sensores

int main(int argc, char *argv[])
{
    semVideo=SDL_CreateMutex();

    //Inicio libreria para controlar video
    if(SDL_Init(SDL_INIT_VIDEO)< 0) {
    	cerr <<"No se puede iniciar SDL:" << SDL_GetError() << endl;
	SDL_Quit();
    } else {
	Uint8 video_bpp;
	Uint32 videoflags;
	videoflags = SDL_HWSURFACE | SDL_SRCALPHA ;
	//int h_screen=SCREEN_H;
	//int v_screen=SCREEN_W;
	const SDL_VideoInfo *info;
	info=SDL_GetVideoInfo();
/*	if ( info->vfmt->BitsPerPixel > 8 ) {
	    video_bpp = info->vfmt->BitsPerPixel;
	} else {
	    video_bpp = 16;
	}*/
	video_bpp=32;
	Uint32 modo=SDL_VideoModeOK(SCREEN_W, SCREEN_H, video_bpp, videoflags);
	if(modo){
	    surfacePrincipal=SDL_SetVideoMode(SCREEN_W, SCREEN_H, video_bpp, videoflags);
	}else {
	    cerr << "El HW no soporta el modo actual" << endl;
	    exit(-1);
	}

	SDL_SetAlpha(surfacePrincipal, SDL_SRCALPHA, 0);
	SDL_FillRect(surfacePrincipal, 0, COLOR_BG);
	SDL_UpdateRect(surfacePrincipal,0,0,0,0);
	pantalla=new Pantalla(surfacePrincipal);
	//Ocultar el cursor
	//pantalla->hideCursor();

	//Cargar el frame donde se sitúa el plano
	framemapa=new Frame(surfacePrincipal);
	framemapa->cargarFrame(
		MARGENH,
		MARGENV,
		(int)((float)SCREEN_W/10.0*6.0), 
		(int)((float)SCREEN_H/10.0*7.5),
		"Plano",0xffffff);
	//plano.lectura("maps/modelo.dxf");
	plano.lectura("maps/cientificot_P1.dxf");
	plano.setFrame(framemapa);
	plano.centrarMapa();
	plano.calcularZoom();
	plano.pintarMapa(surfacePrincipal,plano.getEscala());
	
	silla=new Silla(framemapa,&plano);
	silla->setPos(Punto(100,100));
	silla->dibujar();

	//Cargar el frame donde se sitúa el radar
	frameradar=new Frame(surfacePrincipal);
	frameradar->cargarFrame(
		(int)((float)SCREEN_W/10.0*6.0)+2*MARGENH, 
		SCREEN_H-(int)((float)SCREEN_H/10.0*3.8),
		(int)((float)SCREEN_W/10.0*2.8)+MARGENH, 
		(int)((float)SCREEN_H/10.0*3.5),
		"Radar",
		0xffffff);
	//Mutex para sinc el radar
	mutexSincRadar=SDL_CreateMutex();
	pauseRadar=false;
	condSincRadar=SDL_CreateCond();
	//Cargar el radar en el frame
	radar=new Radar(frameradar);
	mutexObstaculo=SDL_CreateMutex();	
	radar->addObstaculo(Punto(2,50));
	radar->addObstaculo(Punto(20,10));
	radar->addObstaculo(Punto(-10,-10));
	
	//Cargar el frame donde se sitúa el estado
	framestado=new Frame(surfacePrincipal);
	framestado->cargarFrame(
		(int)((float)SCREEN_W/10.0*6.0)+2*MARGENH, 
		MARGENV,
		(int)((float)SCREEN_W/10.0*2.8)+MARGENH, 
		(int)((float)SCREEN_H/10.0*5.0),
		"Estado",
		0xffffff);

	//Instanciar el frame selector de mapas
	frameselector=new Frame(surfacePrincipal);
	//Botones para modificar el zoom del mapa
	botonMasZoom=new Boton(surfacePrincipal);
	botonMasZoom->cargarBoton(
		framemapa->getX()+framemapa->getW()-100, 
		framemapa->getY()+framemapa->getH()+30, 
		20,
		20,
		"+",
		0xFFA500FF,
		COLOR_BORDER_BOTON);

	botonMenosZoom=new Boton(surfacePrincipal);
	botonMenosZoom->cargarBoton(
		framemapa->getX()+framemapa->getW()-50, 
		framemapa->getY()+framemapa->getH()+30, 
		20,
		20,
		"-",
		0xFFA500FF,
		COLOR_BORDER_BOTON);
	
	botonAjustarZoom=new Boton(surfacePrincipal);
	botonAjustarZoom->cargarBoton(
		framemapa->getX()+framemapa->getW()-75, 
		framemapa->getY()+framemapa->getH()+30, 
		20,
		20,
		"[]",
		0xFFA500FF,
		COLOR_BORDER_BOTON);


	//Etiqueta Zoom
	e_zoom=new Etiqueta(surfacePrincipal);
	e_zoom->cargarEtiqueta(framemapa->getX()+framemapa->getW()-100,
		framemapa->getY()+framemapa->getH()+10,
		70,
		20,
		"Zoom",
		0xFFA500FF,
		0x000000FF,
		COLOR_BG);
	e_vzoom=new Etiqueta(surfacePrincipal);
	e_vzoom->cargarEtiqueta(framemapa->getX()+framemapa->getW()-100,
		framemapa->getY()+framemapa->getH()+50,
		70,
		20,
		plano.getEscalaStr(),
		0xFFA500FF,
		0xFFA500FF,
		COLOR_BG);


	//Botones movimiento del mapa
	//	Derecha
	botonDerecha=new Boton(surfacePrincipal);
	botonDerecha->cargarBoton(framemapa->getX()+100, framemapa->getY()+framemapa->getH()+30, 20,20,">",0xFFA500FF,COLOR_BORDER_BOTON);
	//	Izquierda
	botonIzquierda=new Boton(surfacePrincipal);
	botonIzquierda->cargarBoton(framemapa->getX()+60, framemapa->getY()+framemapa->getH()+30, 20,20,"<",0xFFA500FF,COLOR_BORDER_BOTON);
	//	Arriba
	botonArriba=new Boton(surfacePrincipal);
	botonArriba->cargarBoton(framemapa->getX()+80, framemapa->getY()+framemapa->getH()+10, 20,20,"^",0xFFA500FF,COLOR_BORDER_BOTON);
	//	Abajo
	botonAbajo=new Boton(surfacePrincipal);
	botonAbajo->cargarBoton(framemapa->getX()+80, framemapa->getY()+framemapa->getH()+50, 20,20,"V",0xFFA500FF,COLOR_BORDER_BOTON);
	//	Centrar
	botonCentrar=new Boton(surfacePrincipal);
	botonCentrar->cargarBoton(framemapa->getX()+80, framemapa->getY()+framemapa->getH()+30, 20,20,"C",0xFFA500FF,COLOR_BORDER_BOTON);
	//	Selector
	botonSelector=new Boton(surfacePrincipal);
	botonSelector->cargarBoton(framemapa->getX()+10, framemapa->getY()+framemapa->getH()+15, 30,30,"o",0x00000000,0X00000000);
	botonSelector->setIcono("img/mundop.bmp");
	
	botonOnoff=new Boton(surfacePrincipal);
	botonOnoff->cargarBoton(framemapa->getX()+10, framemapa->getY()+framemapa->getH()+50, 30,30,"o",0x00000000,0X00000000);
	botonOnoff->setIcono("img/apagar.bmp");
	//Tabla de estado	
	cconex=new Campo(
		surfacePrincipal,
		"cx GateWay:",
		true,
		0x000000FF,
		0x00FF00FF);
	cconex->valorStr("");
	tcampos.add("CONEX",cconex);
	delete cconex;

	cgrid=new Campo(
		surfacePrincipal,
		"grid:",
		false,
		0x000000FF,
		0x00FF00FF);
	cgrid->valorNum(4,10,2,1);
	tcampos.add("GRID",cgrid);
	delete cgrid;
	
	cdobstaculo=new Campo(
		surfacePrincipal,
		"d_obst:",
		false,
		0x000000FF,
		0x00FF00FF);
	cdobstaculo->valorNum(2,8,2,1);
	tcampos.add("DOBSTACULO",cdobstaculo);
	delete cdobstaculo;

	cprueba=new Campo(
		surfacePrincipal,
		"prueba",
		false,
		0x000000FF,
		0x00FF00FF);
	cprueba->valorNum(2,8,2,1);
	tcampos.add("PRUEBA",cprueba);
	delete cprueba;


	tcampos.recargar(framestado);

	//Actualizar cambios en la pantalla
	SDL_UpdateRect(surfacePrincipal,0,0,0,0);

	//////////  Comunicacion    ////////////
	    //CapaAlta: mapa, camino y objetivo
	mutexCapaAlta=SDL_CreateMutex();
	caminoNuevoCond=SDL_CreateCond();
	clienteCapaAlta.Connect("192.168.1.5", 9999);
	clienteCapaBaja.Connect("192.168.1.5", 9999);
	//clienteCapaAlta.Connect("localhost", 9999);
	GestorCamino gestorCamino(surfacePrincipal);  //Gestiona el estado

	    //CapaBaja: sensores y estado
	mutexCapaBaja=SDL_CreateMutex();
	sensorNuevoCond=SDL_CreateCond();
	//clienteCapaBaja.Connect("192.168.1.5", 9998);
	//GestorEstado gestorEstado;  //Gestiona el estado
	//radar->dibujarFlecha(0);
	//Gestion del input
	while(!pantalla->salir()){
	    pantalla->entrada();
	} 
	delete radar;
	delete pantalla;
 
    }
    SDL_Quit();
    SDL_DestroyMutex(mutexCapaBaja);
    SDL_DestroyMutex(mutexCapaAlta);
    SDL_DestroyMutex(mutexSincRadar);
    SDL_DestroyMutex(mutexObstaculo);
}
