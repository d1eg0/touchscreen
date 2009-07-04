/**
 *       @file  clientecapa_baja.h
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

#ifndef CLIENTECAPABAJA_H
#define CLIENTECAPABAJA_H

#include <SolarSockets/SolarSockets++.h>
#include <fstream>
#include <vector>
#include <SDL/SDL_thread.h>
#include <sstream>
#include <iostream>
#include "punto.h"
using namespace std;
/**
 *  \class ClienteCapaBaja
 *  \brief Gestiona la comunicaci&ocaute;n con el sistema IA. Informaci&oacute;n peri&oacute;dica.
 *   
 *  \par 
 */
class ClienteCapaBaja : public ssPPClient
{
public:
    /** devuelve los valores obtenidos */
    vector<double> getValores();
    /** Conectar con el servidor IA */
    void conectar();
private:
    vector<double> listaValores;
    Punto pos;
    double angulo;
    double sensor[4];
    void onConnect();
    //void onDataArrival(string Data);
    void onLineArrival(string Cadena);
    void onClose();
    void onError(int ssError);
};
#endif

