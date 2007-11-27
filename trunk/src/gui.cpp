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
using namespace std;

SDL_Surface *surfacePrincipal;
Pantalla *pantalla;
//Botones
//  Zoom
Boton *botonMasZoom;
Boton *botonMenosZoom;
//  Desplazar
Boton *botonArriba,
      *botonAbajo,
      *botonDerecha,
      *botonIzquierda,
      *botonCentrar;
// Frames
Frame *framemapa,
      *frameradar,
      *framestado;
// Etiquetas
Etiqueta *e_zoom,
	 *e_vzoom;

Mapa  plano;
Objetivo objetivo;
Radar *radar;
Silla *silla;
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

//Campos de estado
Campo *cconex,
      *cgrid,
      *cdobstaculo,
      *cvelocidad;
//Tabla de campos
Tabla tcampos;
// Comunicacion
ClienteCapaAlta clienteCapaAlta; //Plano y coordenadas
ClienteCapaBaja	clienteCapaBaja; //Sensores

int main(int argc, char *argv[])
{

    semVideo=SDL_CreateMutex();

    string mapadxf="maps/modelo.dxf";
//    string mapadxf="maps/segonDxf.dxf";
    cout <<"Inicializando SDL." << endl;
   
    //Lectura Fichero DXF, introduce la estructura en plano
    DxfParser *parser_dxf=new DxfParser();
    DL_Dxf* dxf = new DL_Dxf();
    if (!dxf->in(mapadxf, parser_dxf)) {
	std::cerr << "No se ha podido abrir el DXF.\n";
    }
    delete dxf;
    delete parser_dxf;
    //Fin lectura Fichero DXF


    //Inicio libreria para controlar video
    if(SDL_Init(SDL_INIT_VIDEO)< 0) {
    	cerr <<"No se puede iniciar SDL:" << SDL_GetError() << endl;
	SDL_Quit();
    } else {
	Uint8 video_bpp;
	Uint32 videoflags;
	videoflags = SDL_HWSURFACE | SDL_SRCALPHA ;//| SDL_FULLSCREEN;
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
	surfacePrincipal=SDL_SetVideoMode(SCREEN_W, SCREEN_H, video_bpp, videoflags);
	//SDL_Surface *surface2=SDL_SetVideoMode(v_screen, h_screen, video_bpp, videoflags);
	SDL_SetAlpha(surfacePrincipal, SDL_SRCALPHA, 0);
	SDL_FillRect(surfacePrincipal, 0, 0x000000);
	SDL_UpdateRect(surfacePrincipal,0,0,0,0);
	pantalla=new Pantalla(surfacePrincipal);

	//Cargar el frame donde se sitúa el plano
	framemapa=new Frame(surfacePrincipal);
	framemapa->cargarFrame(MARGEN,
		MARGEN,
		(int)((float)SCREEN_W/10.0*6.0), 
		(int)((float)SCREEN_H/10.0*7.5),
		"Plano",0xffffff);
	plano.centrarMapa();
	plano.pintarMapa(surfacePrincipal,framemapa,100);
	
	silla=new Silla(framemapa,&plano);
	silla->setPos(Punto(100,100));
	silla->dibujar();

	//Cargar el frame donde se sitúa el radar
	frameradar=new Frame(surfacePrincipal);
	frameradar->cargarFrame(
		(int)((float)SCREEN_W/10.0*6.0)+2*MARGEN, 
		SCREEN_H-(int)((float)SCREEN_H/10.0*4.0),
		(int)((float)SCREEN_W/10.0*2.5)+MARGEN, 
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
		(int)((float)SCREEN_W/10.0*6.0)+2*MARGEN, 
		MARGEN,
		(int)((float)SCREEN_W/10.0*2.5)+MARGEN, 
		(int)((float)SCREEN_H/10.0*5.0),
		"Estado",
		0xffffff);

	//Botones Zoom
	botonMasZoom=new Boton(surfacePrincipal);
	botonMasZoom->cargarBoton(
		framemapa->getX()+framemapa->getW()-100, 
		framemapa->getY()+framemapa->getH()+30, 
		20,
		20,
		"+",
		0xFFA500FF);

	botonMenosZoom=new Boton(surfacePrincipal);
	botonMenosZoom->cargarBoton(
		framemapa->getX()+framemapa->getW()-50, 
		framemapa->getY()+framemapa->getH()+30, 
		20,
		20,
		"-",
		0xFFA500FF);

	//Etiqueta Zoom
	e_zoom=new Etiqueta(surfacePrincipal);
	e_zoom->cargarEtiqueta(framemapa->getX()+framemapa->getW()-100,
		framemapa->getY()+framemapa->getH()+10,
		70,
		20,
		"Zoom",
		0xFFA500FF,
		0x000000FF,
		0x000000FF);
	e_vzoom=new Etiqueta(surfacePrincipal);
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
	botonDerecha=new Boton(surfacePrincipal);
	botonDerecha->cargarBoton(framemapa->getX()+100, framemapa->getY()+framemapa->getH()+30, 20,20,">",0xFFA500FF);
	//	Izquierda
	botonIzquierda=new Boton(surfacePrincipal);
	botonIzquierda->cargarBoton(framemapa->getX()+60, framemapa->getY()+framemapa->getH()+30, 20,20,"<",0xFFA500FF);
	//	Arriba
	botonArriba=new Boton(surfacePrincipal);
	botonArriba->cargarBoton(framemapa->getX()+80, framemapa->getY()+framemapa->getH()+10, 20,20,"^",0xFFA500FF);
	//	Abajo
	botonAbajo=new Boton(surfacePrincipal);
	botonAbajo->cargarBoton(framemapa->getX()+80, framemapa->getY()+framemapa->getH()+50, 20,20,"V",0xFFA500FF);
	//	Centrar
	botonCentrar=new Boton(surfacePrincipal);
	botonCentrar->cargarBoton(framemapa->getX()+80, framemapa->getY()+framemapa->getH()+30, 20,20,"C",0xFFA500FF);

    /*    c1=new Campo(
		framestado,
		"conexion:",
		true);
	c1->valorStr("bad");
	//c1->valorNum(clienteCapaAlta.valor,3,4,5);
	c1->cargarCampo(
		framestado->getXc(),
		framestado->getYc(),
		0x000000FF,
		0x00FF00FF);
    */
	//c1->updateValor(4);
	cconex=new Campo(
		surfacePrincipal,
		"cx camino:",
		true,
		0x000000FF,
		0x00FF00FF);
	cconex->valorStr("mal ");
	tcampos.add("CONEX",cconex);
	delete cconex;

	cgrid=new Campo(
		surfacePrincipal,
		"grid:",
		false,
		0x000000FF,
		0x00FF00FF);
	cgrid->valorNum(4,10,2,1);
	/*cgrid->cargarCampo(
		framestado->getXc(),
		framestado->getYcDown(),
		0x000000FF,
		0x00FF00FF);*/
	tcampos.add("GRID",cgrid);
	delete cgrid;
	cout << "valor:" << tcampos.get("GRID").getVstr() << endl;
	cdobstaculo=new Campo(
		surfacePrincipal,
		"d_obst:",
		false,
		0x000000FF,
		0x00FF00FF);
	cdobstaculo->valorNum(2,8,2,1);
	/*cdobstaculo->cargarCampo(
		framestado->getXc(),
		framestado->getYcDown(),
		0x000000FF,
		0x00FF00FF);*/
	tcampos.add("DOBSTACULO",cdobstaculo);
	delete cdobstaculo;
	tcampos.recargar(framestado);

	//Actualizar cambios en la pantalla
	SDL_UpdateRect(surfacePrincipal,0,0,0,0);

	//////////  Comunicacion    ////////////
	    //CapaAlta: mapa, camino y objetivo
	mutexCapaAlta=SDL_CreateMutex();
	caminoNuevoCond=SDL_CreateCond();
	clienteCapaAlta.Connect("192.168.1.5", 9999);
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
