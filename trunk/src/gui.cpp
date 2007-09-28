#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "pantalla.h"
#include "boton.h"
#include "frame.h"
#include "constantes.h"
#include "dxfparser.h"
#include "mapa.h"
#include <dxflib/dl_dxf.h>
using namespace std;

Boton *boton1;
Frame *framemapa;
Mapa  plano;

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
    cout << "soy un hilo" << endl;
    Pantalla *pantalla=new Pantalla();
    boton1=new Boton(pantalla->getPantalla());
    framemapa=new Frame(pantalla->getPantalla());
    SDL_Color Blanco = {255,255,255,0}; 
    //boton1->CargarBoton(200,200,120,120,0xff);

    SetClip(pantalla->getPantalla(),0,0,500,500);
    //rectangleRGBA(pantalla->GetPantalla(), 5, 5, 100, 100, 255, 0, 0, 255);
    //rectangleColor(pantalla->GetPantalla(), 5, 5, 100, 100, 0xff0000ff);
    //circleRGBA(pantalla->GetPantalla(), 300, 300, 150, 255, 0, 0, 255);
    //circleColor(pantalla->GetPantalla(), 300, 310, 150, 0xff0000ff );
    //SetClip(pantalla->GetPantalla(),0,0,200,200);
    //lineColor(pantalla->GetPantalla(), 0, 0, 100, 100, 0xff0000ff);
    //SDL_UpdateRect(pantalla->GetPantalla(),0,0,0,0);
    framemapa->CargarFrame(0,0,(int)((float)SCREEN_W/10.0*8.0),SCREEN_H,0xf0);
    lineColor(pantalla->getPantalla(), 0, 0, 100, 100, 0xff0000ff);
    //SDL_SetClipRect(pantalla->getPantalla(), (SDL_Rect)&framemapa->getArea() );
    plano.pintarMapa(pantalla->getPantalla(),framemapa);
    SDL_UpdateRect(pantalla->getPantalla(),0,0,0,0);
    while(!pantalla->salir()){
        pantalla->entrada();
    } 
    return 1;
}


int main(int argc, char *argv[])
{


    SDL_Thread *hilo;
    cout <<"Inicializando SDL." << endl;
   
    //Lectura Fichero DXF, introduce la estructura en plano
    DxfParser *parser_dxf=new DxfParser();
    DL_Dxf* dxf = new DL_Dxf();
    if (!dxf->in("maps/casa.dxf", parser_dxf)) {
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
