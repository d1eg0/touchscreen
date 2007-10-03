#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_gfxPrimitives.h>
#include "pantalla.h"
#include "boton.h"
#include "etiqueta.h"
#include "frame.h"
#include "constantes.h"
#include "dxfparser.h"
#include "mapa.h"
#include <dxflib/dl_dxf.h>

using namespace std;
//Botones
Boton *botonMasZoom;
Boton *botonMenosZoom;
Boton *botonArriba,*botonAbajo,*botonDerecha,*botonIzquierda;
/////////
Frame *framemapa;
Etiqueta *e_vzoom;
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

    //Cargar el frame donde se sitúa el plano
    framemapa->cargarFrame(20,20,(int)((float)SCREEN_W/10.0*6.0), (int)((float)SCREEN_H/10.0*6.0),"Plano",0xffffff);
    plano.centrarMapa(pantalla->getPantalla(),framemapa);
    plano.pintarMapa(pantalla->getPantalla(),framemapa,100);

    //Botones Zoom
    botonMasZoom=new Boton(pantalla->getPantalla());
    botonMasZoom->cargarBoton(framemapa->getX()+framemapa->getW()-100, framemapa->getY()+framemapa->getH()+30, 20,20,"+",0xFFA500FF);

    botonMenosZoom=new Boton(pantalla->getPantalla());
    botonMenosZoom->cargarBoton(framemapa->getX()+framemapa->getW()-50, framemapa->getY()+framemapa->getH()+30, 20,20,"-",0xFFA500FF);

    //Etiqueta Zoom
    Etiqueta *e_zoom=new Etiqueta(pantalla->getPantalla());
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
    botonDerecha->cargarBoton(framemapa->getX()+140, framemapa->getY()+framemapa->getH()+30, 20,20,">",0xFFA500FF);
    //	Izquierda
    botonIzquierda=new Boton(pantalla->getPantalla());
    botonIzquierda->cargarBoton(framemapa->getX()+100, framemapa->getY()+framemapa->getH()+30, 20,20,"<",0xFFA500FF);
    //	Arriba
    botonArriba=new Boton(pantalla->getPantalla());
    botonArriba->cargarBoton(framemapa->getX()+120, framemapa->getY()+framemapa->getH()+10, 20,20,"^",0xFFA500FF);
    //	Abajo
    botonAbajo=new Boton(pantalla->getPantalla());
    botonAbajo->cargarBoton(framemapa->getX()+120, framemapa->getY()+framemapa->getH()+50, 20,20,"V",0xFFA500FF);



    //Actualizar cambios en la pantalla
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
