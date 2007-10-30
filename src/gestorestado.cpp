#include <iostream>
#include "gestorestado.h"
int initEstado(void *p);
GestorEstado::GestorEstado(){
    gestor = SDL_CreateThread(initEstado, NULL);
}
GestorEstado::~GestorEstado(){
    SDL_KillThread(gestor);
}
int initEstado(void *p){
    while(1){
	cout<< "gestor estado" << endl;
	SDL_Delay(5000);
    }
    return 1;
}
