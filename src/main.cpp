#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "pantalla.h"
using namespace std;

int main(int argc, char *argv[])
{
 	cout <<"Inicializando SDL." << endl;
  	/* Initializes Audio and the CDROM, add SDL_INIT_VIDEO for Video */
  	if(SDL_Init(SDL_INIT_VIDEO)< 0) {
    	cout <<"No se puede iniciar SDL:" << SDL_GetError() << endl;
       	SDL_Quit();
  	} else {
		Pantalla *pantalla=new Pantalla();
		while(!pantalla->Salir()){
        	pantalla->Entrada();
		}

    }
  	SDL_Quit();
}
