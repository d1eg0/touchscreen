/**
 *       @file  mapa.h
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
    /** Instancia del mapa */
    Mapa();
    ~Mapa();

    /** Devuelve la ruta del mapa actual */
    string getPath();
    /** Lectura de un mapa situado en 'ruta' */
    void lectura(string ruta);
    /** Duelve el desplazamiento horizontal del origen */
    double getDH();
    /** Duelve el desplazamiento vertical del origen */
    double getDV();
    /** Duelve la escala del mapa en formato num&eacute;rico */
    double getEscala();
    /** Duelve la escala del mapa en formato cadena */
    char* getEscalaStr();
    /** Devuelve las capas que contiene el mapa */
    vector<Capa>* getMapa();   
    /** Devuelve la capa de nombre 'c' */
    Capa* getCapa(string c);
    /** A&ntilde; la capa 'capa' al mapa */
    void addCapa(Capa capa);
    /** El camino al objetivo pasa a ser 'c' */
    void setCamino(vector<Linea> c);
    /** Borrar camino */
    void clearCamino();
    /** Borra las capas del mapa */
    void clearMapa();
    /** Escala el mapa a 'escala' */
    void escalarMapa(double escala);
    /** Pinta el mapa en la superficie 'screen', en el frame 'frame', a escala 'escala' */
    void pintarMapa(SDL_Surface *screen, double escala);
    /** Pinta el camino en la superficie 'screen', en el frame 'frame', a escala 'escala' */
    void pintarCamino(SDL_Surface *screen,Frame *frame, double escala);
    /** Calculo de los desplazamientos para el centrado */
    void calcularDHV(Frame *frame);
    /** Centra el mapa */
    void centrarMapa();
    /** Calcular el zoom para ajustar el mapa a la ventana */
    void calcularZoom();
    /** Frame donde se pintara */
    void setFrame(Frame *frame);

    //Desplazamientos
    /** Desplaza el mapa arriba */
    void despArriba();
    /** Desplaza el mapa abajo */
    void despAbajo();
    /** Desplaza el mapa a la izquierda */
    void despIzquierda();
    /** Desplaza el mapa a la derecha */
    void despDerecha();

private:
    string path;
    vector<Capa> listaCapas;
    vector<Linea> camino;
    Dibujar *pincel;
    Frame *frame;
    double escala; //0%..100%
    double escalaOptima; //0%..100%
    
    //Desplazamientos para el centrado: horizontal y vertical
    double dh;
    double dv;
    //Centro visual
    double xm;
    double ym;
      
};
#endif

