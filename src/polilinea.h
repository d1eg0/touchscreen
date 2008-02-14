/**
 *   \file  polilinea.h
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
#include "punto.h"
#include "linea.h"
using namespace std;

/**
 *  \class Polilinea
 *  \brief La clase Capa est&aacute; divida en Polilineas de vertices
 *   
 *  \par 
 */

class Polilinea {
public:
    /** Instancia de una polil&iacute;nea en la capa 'capa', con 'num' v&eacute;rtices, 'cerrado' si es cerrado o abierto */
    Polilinea(int num, bool cerrado, string capa);
    ~Polilinea();

    /** Devuelve la lista de puntos de la polil&iacute;nea */
    vector<Punto>* getPolilinea();
    /** A&ntilde;adir un v&eacute; a la polil&iacute;nea */
    void addVertice(Punto vertice);
    /** Devuelve si la polil&iacute;nea es cerrada */
    bool getCerrado();
    /** Devuelve el n&uacute;mero total de v&eacute;rtices de la polil&iacute;nea */
    int getNumTotal();
    /** Devuelve el n&uacute;mero de v&eacute;rtices de la polil&iacute;nea */
    int getNum();
    /** Transforma la lista de puntos de la polil&iacute;nea en l&iacute;neas */
    vector<Linea> toLineas();
    /** Poner nombre a la polil&iacute;nea como habitaci&oacute;n */
    void setHabitacion(string nombre);
    /** Devuelve el nombre de la habitaci&oacute;n */
    string getHabitacion();
private:
    string capa;
    string nombre_hab;
    vector<Punto> listaVertices;
    bool cerrado;
    int numVertices;
};
#endif

