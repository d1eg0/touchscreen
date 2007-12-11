#include <iostream>
#include "gestorcamino.h"
#include <vector>
#include "punto.h"
#include "clientecapa_alta.h"
#include "constantes.h"
#include "frame.h"
#include "polilinea.h"
#include "mapa.h"
#include "pantalla.h"
#include "etiqueta.h"
#include <algorithm>

extern ClienteCapaAlta clienteCapaAlta;
extern SDL_mutex *mutexCapaAlta;
extern SDL_cond *caminoNuevoCond;
extern Mapa plano;
extern Pantalla *pantalla;
int threadCamino(void *p);

GestorCamino::GestorCamino(SDL_Surface *surface){
    gestor = SDL_CreateThread(threadCamino, (void*)surface);
}
GestorCamino::~GestorCamino(){
    SDL_KillThread(gestor);
}

int threadCamino(void *p){
    SDL_Surface *screen=(SDL_Surface*)p;
    extern Frame *framemapa;
    double v=0;
    vector<Punto> listaPuntos;

    SDL_mutexP(mutexCapaAlta);
    listaPuntos=clienteCapaAlta.getCamino();
    SDL_mutexV(mutexCapaAlta);
    while(1){
	SDL_mutexP(mutexCapaAlta);
	cout<< "gestor camino: espero" << endl;
	SDL_CondWait( caminoNuevoCond, mutexCapaAlta);
	cout<< "gestor camino: sigo" << endl;
	vector<Punto> tlistaPuntos;

	listaPuntos=clienteCapaAlta.getCamino();
	clienteCapaAlta.clearCamino();	

	Polilinea camino(0,false,"");	

	if(listaPuntos.empty()){
	    cout << "Error: camino no posible" << endl;
	    pantalla->setHandle(false);
	    pantalla->setAlpha(framemapa,Z_CENTRO);
	    Etiqueta error(pantalla->getPantalla());
	    string msgerror="No hay camino a ese punto";
	    error.cargarEtiqueta(
		   (int)((framemapa->getX()+framemapa->getW()*0.5)-(msgerror.size()*SIZE_C*0.5)), 
		   (int)((framemapa->getY()+framemapa->getW()*0.5)-SIZE_C*0.5), 
		   SIZE_C*msgerror.size()+20, 
		   20, 
		   (char*)msgerror.c_str(), 
		   0xff0000ff, 
		   0xffffffff, 
		   0x00000030 );
	    SDL_Delay(2000);
	    plano.pintarMapa(pantalla->getPantalla(),framemapa,plano.getEscala());
	    pantalla->setHandle(true);

	}else{ 
	    cout << "hay algo" << endl;
	    cout << "x:" << listaPuntos.front().getX() << 
		"y:" << listaPuntos.front().getY() << endl;
	    vector<Punto>::iterator i_punto;
	    for(i_punto=listaPuntos.begin();i_punto!=listaPuntos.end();i_punto++)
		camino.addVertice((*i_punto));
	    vector<Linea>caminoLineas=camino.toLineas();
	    plano.setCamino(caminoLineas);
	    plano.pintarCamino(screen,framemapa,plano.getEscala());
	    
	}
	SDL_mutexV(mutexCapaAlta);
    }
    return 1;
}