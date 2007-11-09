#include "gestorestado.h"

extern SDL_cond *sensorNuevoCond;
extern SDL_mutex *mutexCapaBaja;
extern ClienteCapaBaja clienteCapaBaja;

int initEstado(void *p);
GestorEstado::GestorEstado(){
    gestor = SDL_CreateThread(initEstado, NULL);
}
GestorEstado::~GestorEstado(){
    SDL_KillThread(gestor);
}
int initEstado(void *p){
    while(1){
	SDL_mutexP(mutexCapaBaja);
	cout<< "gestor estado: Espero" << endl;
	SDL_CondWait(sensorNuevoCond, mutexCapaBaja);
	cout<< "gestor estado: Sigo" << endl;
	vector<double> valores=clienteCapaBaja.getValores();
	SDL_mutexV(mutexCapaBaja);
    }
    return 1;
}
