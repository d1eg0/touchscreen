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
#include "campotexto.h"
#include "objetivo.h"
using namespace std;
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
Etiqueta *e_zoom,
	 *e_vzoom;
Mapa  plano;
Objetivo objetivo;
void SetClip (SDL_Surface *screen, int x1, int y1, int x2, int y2)
{
    SDL_Rect clip;
    clip.x = x1+BORDER;
    clip.y = y1+BORDER;
    clip.w = x2-x1-2*BORDER;
    clip.h = y2-y1-2*BORDER;
    SDL_SetClipRect(screen, &clip);
}

int gestor (void *unusued){
    Pantalla *pantalla=new Pantalla();
    SDL_Color Blanco = {255,255,255,0}; 

    SetClip(pantalla->getPantalla(),0,0,500,500);

    //Cargar el frame donde se sitúa el plano
    framemapa=new Frame(pantalla->getPantalla());
    framemapa->cargarFrame(MARGEN,
	    MARGEN,
	    (int)((float)SCREEN_W/10.0*6.0), 
	    (int)((float)SCREEN_H/10.0*8.0),
	    "Plano",0xffffff);
    plano.centrarMapa(pantalla->getPantalla(),framemapa);
    plano.pintarMapa(pantalla->getPantalla(),framemapa,100);

    //Cargar el frame donde se sitúa el plano
    frameradar=new Frame(pantalla->getPantalla());
    frameradar->cargarFrame(
	    (int)((float)SCREEN_W/10.0*6.0)+2*MARGEN, 
	    SCREEN_H-(int)((float)SCREEN_H/10.0*4.0),
	    (int)((float)SCREEN_W/10.0*2.5)+MARGEN, 
	    (int)((float)SCREEN_H/10.0*4.0),
	    "Radar",
	    0xffffff);

    //Cargar el frame donde se sitúa el plano
    framestado=new Frame(pantalla->getPantalla());
    framestado->cargarFrame(
	    (int)((float)SCREEN_W/10.0*6.0)+2*MARGEN, 
	    MARGEN,
	    (int)((float)SCREEN_W/10.0*2.5)+MARGEN, 
	    (int)((float)SCREEN_H/10.0*5.5),
	    "Estado",
	    0xffffff);

    //Botones Zoom
    botonMasZoom=new Boton(pantalla->getPantalla());
    botonMasZoom->cargarBoton(
	    framemapa->getX()+framemapa->getW()-100, 
	    framemapa->getY()+framemapa->getH()+30, 
	    20,
	    20,
	    "+",
	    0xFFA500FF);

    botonMenosZoom=new Boton(pantalla->getPantalla());
    botonMenosZoom->cargarBoton(
	    framemapa->getX()+framemapa->getW()-50, 
	    framemapa->getY()+framemapa->getH()+30, 
	    20,
	    20,
	    "-",
	    0xFFA500FF);

    //Etiqueta Zoom
    e_zoom=new Etiqueta(pantalla->getPantalla());
    e_zoom->cargarEtiqueta(framemapa->getX()+framemapa->getW()-100,
	    framemapa->getY()+framemapa->getH()+10,
	    70,
	    20,
	    "Zoom",
	    0xFFA500FF,
	    0x000000FF,
	    0x000000FF);
    e_vzoom=new Etiqueta(pantalla->getPantalla());
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
    botonDerecha=new Boton(pantalla->getPantalla());
    botonDerecha->cargarBoton(framemapa->getX()+100, framemapa->getY()+framemapa->getH()+30, 20,20,">",0xFFA500FF);
    //	Izquierda
    botonIzquierda=new Boton(pantalla->getPantalla());
    botonIzquierda->cargarBoton(framemapa->getX()+60, framemapa->getY()+framemapa->getH()+30, 20,20,"<",0xFFA500FF);
    //	Arriba
    botonArriba=new Boton(pantalla->getPantalla());
    botonArriba->cargarBoton(framemapa->getX()+80, framemapa->getY()+framemapa->getH()+10, 20,20,"^",0xFFA500FF);
    //	Abajo
    botonAbajo=new Boton(pantalla->getPantalla());
    botonAbajo->cargarBoton(framemapa->getX()+80, framemapa->getY()+framemapa->getH()+50, 20,20,"V",0xFFA500FF);
    //	Centrar
    botonCentrar=new Boton(pantalla->getPantalla());
    botonCentrar->cargarBoton(framemapa->getX()+80, framemapa->getY()+framemapa->getH()+30, 20,20,"C",0xFFA500FF);

    Campotexto *c1=new Campotexto(
	    framestado,
	    "campo:",
	    3,
	    4,
	    5,
	    6
	    );
    c1->cargarCampotexto(
	    framestado->getXc(),
	    framestado->getYc(),
	    0x000000FF,
	    0x00FF00FF);
    Campotexto *c2=new Campotexto(
	    framestado,
	    "campo:",
	    3,
	    4,
	    5,
	    6
	    );
    c2->cargarCampotexto(
	    framestado->getXc(),
	    framestado->getYc(),
	    0x000000FF,
	    0x00FF00FF);


    //Actualizar cambios en la pantalla
    SDL_UpdateRect(pantalla->getPantalla(),0,0,0,0);
    while(!pantalla->salir()){
        pantalla->entrada();
    } 
    return 1;
}


int main(int argc, char *argv[])
{
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
	//Hilo que genera el GUI
	hilo = SDL_CreateThread(gestor, NULL);
	if (hilo == NULL){
		cerr << "No se ha podido crear el hilo" << endl;
	}
	SDL_WaitThread(hilo, NULL);
    }
    SDL_Quit();
}
