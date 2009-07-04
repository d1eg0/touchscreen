/**
 *       @file  gestorestado.cpp
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

#include "gestorestado.h"

extern SDL_cond *sensorNuevoCond;
extern SDL_mutex *mutexCapaBaja;
extern ClienteCapaBaja clienteCapaBaja;

int threadEstado(void *p);
GestorEstado::GestorEstado(){
    gestor = SDL_CreateThread(threadEstado, NULL);
}
GestorEstado::~GestorEstado(){
    SDL_KillThread(gestor);
}
int threadEstado(void *p){
    while(1){
	SDL_mutexP(mutexCapaBaja);
	cout<< "gestor estado: Espero" << endl;
	SDL_CondWait(sensorNuevoCond, mutexCapaBaja);
	cout<< "gestor estado: Nueva INFO" << endl;
	vector<double> valores=clienteCapaBaja.getValores();
	SDL_mutexV(mutexCapaBaja);
    }
    return 1;
}
