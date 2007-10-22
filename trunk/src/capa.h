/**
 *    \file  capa.h
 *   \brief  
 *
 *  Detailed description starts here.
 *
 *  \author  Diego García Valverde , kobydiego@gmail.com
 *
 *  \internal
 *    Created:  26/09/07
 *   Compiler:  gcc/g++
 *    Company:  UIB
 *
 *  This source code is released for free distribution under the terms of the
 *  GNU General Public License as published by the Free Software Foundation.
 * =====================================================================================
 */
#ifndef CAPA_H
#define CAPA_H

#include <iostream>
#include <vector>
#include "linea.h"
#include "polilinea.h"
#include "punto.h"

using namespace std;

/**
 *  \class Capa
 *  \brief La clase Mapa está divida en capas
 *   
 *  \par 
 */

class Capa {
public:
    Capa(string nombre, int color);
    ~Capa();

    vector<Linea>* getCapa();
    vector<Polilinea>* getPolilinea();
    void addLinea(Linea linea);
    void addPolilinea(Polilinea polilinea);
    void addVertice(Punto vertice);
    int getColor();
    string getNombre();
    void clear();
private:
    vector<Linea> listaLineas;
    vector<Polilinea> listaPolilineas;
    string nombre;
    int color;
};
#endif

