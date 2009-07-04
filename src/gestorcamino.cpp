/**
 *       @file  gestorcamino.cpp
 *
 *     @author  Diego García , kobydiego@gmail.com
 *
 *   @internal
 *     Company  Universitat de les Illes Balears
 *   Copyright  Copyright (c) 2009, Diego García
 *
 *
 *  This file is part of TouchScreenGUI.
 *  TouchScreenGUI is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  TouchScreenGUI is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TouchScreenGUI; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  http://www.gnu.org/copyleft/gpl.html
 *
 * =====================================================================================
 */

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
#include "silla.h"

extern ClienteCapaAlta clienteCapaAlta;
extern SDL_mutex *mutexCapaAlta;
extern SDL_cond *caminoNuevoCond;
extern Mapa plano;
extern Pantalla *pantalla;
extern Silla *silla;
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
    /////////////////////////////////////////////////

    Polilinea camino(0,false,"");	
    camino.addVertice(Punto(21.422045,14.318125));
    camino.addVertice(Punto(20.222045,-0.881875));
    camino.addVertice(Punto(20.222045,-11.681875));
    camino.addVertice(Punto(20.622045,-12.081875));
    camino.addVertice(Punto(21.422045,-12.081875));
    camino.addVertice(Punto(22.622045,-13.281875));
    vector<Linea>caminoLineas=camino.toLineas();
    plano.setCamino(caminoLineas);
    plano.pintarCamino(screen,framemapa,plano.getEscala());
    silla->setPos(Punto(21.422045,14.318125));
    silla->dibujar();

    ////////////////////////////////////////////////
    while(1){
	SDL_mutexP(mutexCapaAlta);
	cout<< "gestor camino: espero" << endl;
	SDL_CondWait( caminoNuevoCond, mutexCapaAlta);
	cout<< "gestor camino: sigo" << endl;
	vector<Punto> tlistaPuntos;

	listaPuntos=clienteCapaAlta.getCamino();
	clienteCapaAlta.clearCamino();	
	plano.clearCamino();

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
	    plano.pintarMapa(pantalla->getPantalla(),plano.getEscala());
	    pantalla->minimizar();
	    pantalla->setHandle(true);

	}else{ 
	    plano.pintarMapa(pantalla->getPantalla(),plano.getEscala());
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
