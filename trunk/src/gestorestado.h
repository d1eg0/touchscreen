/**
 *       @file  gestorestado.h
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

#ifndef GESTORESTADO_H
#define GESTORESTADO_H
#include <SDL/SDL_thread.h>
#include <SDL/SDL.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "clientecapa_baja.h"

/**
 *  \class GestorEstado
 *  \brief Hilo que realiza la lectura de los valores de los sensores cuando se reciben
 *   
 *  \par 
 */

using namespace std;
class GestorEstado{
public:
    GestorEstado();
    ~GestorEstado();
private:
    SDL_Thread *gestor;
    

};
#endif
