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
#include "dibujar.h"
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

    void setOrigen(int x, int y);
    double getOX();
    double getOY();
    double getDH();
    double getDV();
    double getEscala();
    char* getEscalaStr();
    vector<Capa>* getMapa();   
    void addCapa(Capa capa);
    void clearMapa();
    void escalarMapa(int escala);
    void pintarMapa(SDL_Surface *screen,Frame *frame, int escala);
    //Calculo de los desplazamientos para el centrado
    void calcularDHV(SDL_Surface *screen, Frame *frame);
    void centrarMapa(SDL_Surface *screen, Frame *frame);

    //Desplazamientos
    void despArriba();
    void despAbajo();
    void despIzquierda();
    void despDerecha();

private:
    vector<Capa> listaCapas;
    Dibujar *pincel;
    Frame *frame;
    int escala; //0%..100%
    
    //Origen 0,0
    double ox;
    double oy;
    //Desplazamientos para el centrado: horizontal y vertical
    double dh;
    double dv;
    //Centro visual
    double xm;
    double ym;
      
};
#endif

