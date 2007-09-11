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
   		SDL_Event event;
		Pantalla *pantalla=new Pantalla();
		SDL_Cursor* cursor=SDL_CreateCursor((Uint8*)1, (Uint8*)0,10,10,300,300);
        SDL_Delay(5000);
	
			cout << "x:"<< SDL_GetCursor()->hot_x << " y:" << SDL_GetCursor()->hot_y << endl;

        
		//cout << "x:"<< cursor->hot_x << " y:" << cursor->hot_y << endl;
    }
  	SDL_Quit();
}
