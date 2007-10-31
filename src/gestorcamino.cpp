#include <iostream>
#include "gestorcamino.h"
#include <vector>
#include "punto.h"
#include "clientecapa_alta.h"
#include "constantes.h"
#include "campo.h"
#include "frame.h"
#include "polilinea.h"
#include "mapa.h"
#include <algorithm>
extern ClienteCapaAlta clienteCapaAlta;
extern SDL_mutex *mutexCapaAlta;
extern Campo *c2;
extern Mapa plano;
int initCamino(void *p);
GestorCamino::GestorCamino(SDL_Surface *surface){
    gestor = SDL_CreateThread(initCamino, (void*)surface);
}
GestorCamino::~GestorCamino(){
    SDL_KillThread(gestor);
}
bool iguales (Punto p1, Punto p2) {
    return ((p1.getX()==p2.getX())&&(p1.getY()==p2.getY()));
}
int initCamino(void *p){
    SDL_Surface *screen=(SDL_Surface*)p;
    extern Frame *framemapa;
    double v=0;
    vector<Punto> listaPuntos;

    SDL_mutexP(mutexCapaAlta);
    listaPuntos=clienteCapaAlta.getCamino();
    SDL_mutexV(mutexCapaAlta);
    while(1){
	SDL_mutexP(mutexCapaAlta);
	cout<< "gestor camino" << endl;
	vector<Punto> tlistaPuntos;
	if(clienteCapaAlta.caminoNuevo()){
	    listaPuntos=clienteCapaAlta.getCamino();
	    /*tlistaPuntos=clienteCapaAlta.getCamino();
	    
	    if(equal(tlistaPuntos.begin(),tlistaPuntos.end(),listaPuntos.begin(),iguales)){
		cout << "camino igual" << endl;
	    }
	    else 
		cout << "camino diferente" << endl;
	    */
	    Polilinea camino(0,false,"");	

	    if(listaPuntos.empty()) cout << "lista vacia" << endl;
	    else{ 
		cout << "hay algo" << endl;
		cout << "x:" << listaPuntos.front().getX() << 
		    "y:" << listaPuntos.front().getY() << endl;
		c2->updateValor("ok");   
		vector<Punto>::iterator i_punto;
		for(i_punto=listaPuntos.begin();i_punto!=listaPuntos.end();i_punto++)
		    camino.addVertice((*i_punto));
		framemapa->activarFrame();
		vector<Linea>caminoLineas=camino.toLineas();
		plano.setCamino(caminoLineas);
		plano.pintarCamino(screen,framemapa,plano.getEscala());
		SDL_UpdateRect(screen, 0, 0, SCREEN_W, SCREEN_H);
	    }
	}
	
	SDL_mutexV(mutexCapaAlta);
	SDL_Delay(5000);
    }
    return 1;
}
