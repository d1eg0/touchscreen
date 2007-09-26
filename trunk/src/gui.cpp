#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include "pantalla.h"
#include "boton.h"
#include "frame.h"
#include "constantes.h"
#include "dxfparser.h"
#include <dxflib/dl_dxf.h>
using namespace std;

Boton *boton1;
Frame *mapa;
int gestor (void *unusued){
    cout << "soy un hilo" << endl;
    Pantalla *pantalla=new Pantalla();
    boton1=new Boton(pantalla->GetPantalla());
    mapa=new Frame(pantalla->GetPantalla());
    SDL_Color Blanco = {255,255,255,0}; 
    boton1->CargarBoton(200,200,120,120,0xff);
    mapa->CargarFrame(0,0,(int)((float)SCREEN_W/10.0*8.0),SCREEN_H,0xf0);
	//SDL_MapRGB( pantalla->GetPantalla()->format, 0, 200, 0 ), &Blanco);
    while(!pantalla->Salir()){
        pantalla->Entrada();
    } 
    return 1;
}

int main(int argc, char *argv[])
{
    SDL_Thread *hilo;
    cout <<"Inicializando SDL." << endl;
    
    //Lectura Fichero DXF
    DxfParser *parser_dxf=new DxfParser();
    DL_Dxf* dxf = new DL_Dxf();
    if (!dxf->in("casa.dxf", parser_dxf)) {
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
