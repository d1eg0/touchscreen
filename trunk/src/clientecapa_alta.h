/**
 *       @file  clientecapa_alta.h
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

#ifndef CLIENTECAPAALTA_H
#define CLIENTECAPAALTA_H

#include <SolarSockets/SolarSockets++.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "punto.h"
/**
 *  \class ClienteCapaAlta
 *  \brief Gestiona la comunicaci&oacute;n con el sistema IA. Informaci&oacute;n aperi&oacute;dica.
 *   
 *  \par 
 */
class ClienteCapaAlta : public ssPPClient
{
public:
    /** Carga el mapa situado en "path" */
    void setMap(string path);
    /** Obtiene el camino guardado */
    vector<Punto> getCamino();
    /** Borra el camino guardado */
    void clearCamino();
    /** Envia el plano situado en "path" al sistema IA */
    void enviarPlano(string path);
    /** Envia la informaci&oacute;n "dato" al sistema IA */
    void enviar(string dato);
    /** Conecta con el sistema IA */
    void conectar();
private:
    string modo;
    double status;
    stringstream buffer;
    vector<Punto> listaPuntos;
    string path;
    void onConnect();
    void onClose();
    void onLineArrival(string Cadena);
    void onError(int ssError);
};
#endif

