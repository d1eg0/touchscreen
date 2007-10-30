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
using namespace std;
SDL_Surface *surfacePrincipal;
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
// Mutex
SDL_mutex *mutexCapaAlta;
Campo *c2;
// Comunicacion
ClienteCapaAlta clienteCapaAlta; //Plano y coordenadas
//ClienteCapaBaja	clienteCapaBaja; //Sensores
void SetClip (SDL_Surface *screen, int x1, int y1, int x2, int y2)
{
    SDL_Rect clip;
    clip.x = x1+BORDER;
    clip.y = y1+BORDER;
    clip.w = x2-x1-2*BORDER;
    clip.h = y2-y1-2*BORDER;
    SDL_SetClipRect(screen, &clip);
}

int main(int argc, char *argv[])
{
    mutexCapaAlta=SDL_CreateMutex();
    string mapadxf="maps/modelo.dxf";
//    string mapadxf="maps/segonDxf.dxf";
    SDL_Thread *hilo;
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
	videoflags = SDL_SWSURFACE | SDL_SRCALPHA ;
	int h_screen=SCREEN_H;
	int v_screen=SCREEN_W;
	const SDL_VideoInfo *info;
	info=SDL_GetVideoInfo();
	if ( info->vfmt->BitsPerPixel > 8 ) {
	    video_bpp = info->vfmt->BitsPerPixel;
	} else {
	    video_bpp = 16;
	}
	surfacePrincipal=SDL_SetVideoMode(v_screen, h_screen, video_bpp, videoflags);
	SDL_SetAlpha(surfacePrincipal, SDL_SRCALPHA, 0);
	SDL_FillRect(surfacePrincipal, 0, 0x000000);
	SDL_UpdateRect(surfacePrincipal,0,0,0,0);
    
	Pantalla *pantalla=new Pantalla(surfacePrincipal);
	SDL_Color Blanco = {255,255,255,0}; 

	SetClip(surfacePrincipal,0,0,500,500);

	//Cargar el frame donde se sitúa el plano
	framemapa=new Frame(surfacePrincipal);
	framemapa->cargarFrame(MARGEN,
		MARGEN,
		(int)((float)SCREEN_W/10.0*6.0), 
		(int)((float)SCREEN_H/10.0*8.0),
		"Plano",0xffffff);
	plano.centrarMapa();
	plano.pintarMapa(surfacePrincipal,framemapa,100);

	//Cargar el frame donde se sitúa el radar
	frameradar=new Frame(surfacePrincipal);
	frameradar->cargarFrame(
		(int)((float)SCREEN_W/10.0*6.0)+2*MARGEN, 
		SCREEN_H-(int)((float)SCREEN_H/10.0*4.0),
		(int)((float)SCREEN_W/10.0*2.5)+MARGEN, 
		(int)((float)SCREEN_H/10.0*4.0),
		"Radar",
		0xffffff);

	//Cargar el frame donde se sitúa el estado
	framestado=new Frame(surfacePrincipal);
	framestado->cargarFrame(
		(int)((float)SCREEN_W/10.0*6.0)+2*MARGEN, 
		MARGEN,
		(int)((float)SCREEN_W/10.0*2.5)+MARGEN, 
		(int)((float)SCREEN_H/10.0*5.5),
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
	c2=new Campo(
		surfacePrincipal,
		"campo:",
		true);
	c2->valorStr("bad");
	c2->cargarCampo(
		framestado->getXc(),
		framestado->getYc(),
		0x000000FF,
		0x00FF00FF);


	//Actualizar cambios en la pantalla
	SDL_UpdateRect(surfacePrincipal,0,0,0,0);
	clienteCapaAlta.Connect("localhost", 9999);
	//GestorEstado gestorEstado;  //Gestiona el estado
	GestorCamino gestorCamino(surfacePrincipal);  //Gestiona el estado
	
	//clienteCapaBaja.Connect("localhost", 9999);

	while(!pantalla->salir()){
	    pantalla->entrada();
	} 
 
//SDL_Delay(5000);
	//Hilo que genera el GUI
//	hilo = SDL_CreateThread(gestor, surfacePrincipal);
//	if (hilo == NULL){
//		cerr << "No se ha podido crear el hilo que gestiona la interfaz" << endl;
//	}
//	SDL_WaitThread(hilo, NULL);
    }
    //SDL_KillThread(gestorCapaAlta);
    SDL_Quit();
}
