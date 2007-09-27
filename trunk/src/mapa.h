/**
 *    \file  mapa.h
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
#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include "capa.h"
#include "frame.h"
using namespace std;
/**
 *  \class Mapa
 *  \brief Organiza las capas del fichero dxf
 *   
 *  \par 
 */
class Mapa {
public:
    Mapa();
    ~Mapa();

    vector<Capa>* getMapa();   
    void addCapa(Capa capa);
    void clearMapa();
    void pintarMapa(Frame *frame);
private:
    vector<Capa> listaCapas;

      
};
#endif

