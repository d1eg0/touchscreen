/**
 *    \file  Polilinea.h
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
#ifndef POLILINEA_H
#define POLILINEA_H

#include <iostream>
#include <vector>
#include "vertice.h"
#include "linea.h"
using namespace std;

/**
 *  \class Polilinea
 *  \brief La clase Capa está divida en Polilineas de vertices
 *   
 *  \par 
 */

class Polilinea {
public:
    Polilinea(int num, bool cerrado, string capa);
    ~Polilinea();

    vector<Vertice>* getPolilinea();
    void addVertice(Vertice vertice);
    bool getCerrado();
    int getNumTotal();
    int getNum();
    vector<Linea> toLineas();
private:
    string capa;
    vector<Vertice> listaVertices;
    bool cerrado;
    int numVertices;
};
#endif

