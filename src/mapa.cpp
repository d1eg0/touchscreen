/**
 *    \file  mapa.cpp
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
#include "mapa.h"

Mapa::Mapa(){
}

Mapa::~Mapa(){
    listaCapas.clear();
}

vector<Capa>* Mapa::getMapa(){
    return &listaCapas;
}

void Mapa::addCapa(Capa capa){
    listaCapas.push_back(capa);
}

void Mapa::clearMapa(){
    listaCapas.clear();
}


void Mapa::pintarMapa(SDL_Surface *screen, Frame *frame){   
    pincel=new Dibujar(screen);

     vector<Capa>::iterator i_capa;
     vector<Linea>::iterator i_linea;
     for(i_capa=this->listaCapas.begin(); i_capa!=this->listaCapas.end(); i_capa++){
	 cout << "Capa:" << (*i_capa).getNombre() << "," << (*i_capa).getColor() << ",size:" << (*(*i_capa).getCapa()).size() << endl;
	 vector<Linea> llineas=(*(*i_capa).getCapa());
	 for(i_linea=llineas.begin(); i_linea!=llineas.end(); i_linea++){
	     Linea linealeida=(*i_linea);
	     printf("LINE     (%lf, %lf) (%lf, %lf)\n",linealeida.getX1(),linealeida.getY1(), linealeida.getX2(),linealeida.getY2());
	     pincel->dibujarLinea(frame,&linealeida);
	 }
     }
}
