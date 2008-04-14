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
 *  \brief La clase Mapa est&aacute; divida en capas
 *   
 *  \par 
 */

class Capa {
public:
    Capa();
    /** Instanciar una nueva capa con nombre 'nombre' */ 
    Capa(string nombre);
    ~Capa();
    /** Obtener las l&iacute;neas de la capa */
    vector<Linea>* getCapa();
    /** Obtener las polil&iacute;neas de la capa */
    vector<Polilinea>* getPolilinea();
    /** Añadir una l&iacute; a la capa */
    void addLinea(Linea linea);
    /** Añadir una polil&iacute; a la capa */
    void addPolilinea(Polilinea polilinea);
    /** Añadir un v&eacute;rtice a la capa */
    void addVertice(Punto vertice);
    /** Obtener el nombre de la capa */
    string getNombre();
    /** Limpiar el vector de polil&iacute;neas */
    void clear();
private:
    vector<Linea> listaLineas;
    vector<Polilinea> listaPolilineas;
    string nombre;
};
#endif

