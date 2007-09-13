#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include "pantalla.h"
#include "boton.h"
using namespace std;

int gestor (void *unusued){
	cout << "soy un hilo" << endl;
	Pantalla *pantalla=new Pantalla();
	Boton *boton1=new Boton(pantalla->GetPantalla());
	SDL_Color Blanc = {255,255,255,0}; 
	boton1->CargarBoton(200,200,20,20,"hola",SDL_MapRGB( pantalla->GetPantalla()->format, 0, 200, 0 ), &Blanc);
	boton1->DibujarBoton();
		while(!pantalla->Salir()){
        	pantalla->Entrada();
		} 
	return 1;
}

int main(int argc, char *argv[])
{
	SDL_Thread *hilo;
 	cout <<"Inicializando SDL." << endl;
  	
	if(SDL_Init(SDL_INIT_VIDEO)< 0) {
    	cerr <<"No se puede iniciar SDL:" << SDL_GetError() << endl;
       	SDL_Quit();
  	} else {
		hilo = SDL_CreateThread(gestor, NULL);
		if (hilo == NULL){
			cerr << "No se ha podido crear el hilo" << endl;
		}
		SDL_WaitThread(hilo, NULL);
    }
  	SDL_Quit();
}
