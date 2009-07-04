/**
 *       @file  objetivo.h
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

#ifndef OBJETIVO_H
#define OBJETIVO_H
#include "polilinea.h"
#include "frame.h"
#include "mapa.h"
#include "boton.h"

/**
 *  \class Objetivo
 *  \brief Clase que gestiona el objetivo establecido
 *   
 *  \par 
 */
class Objetivo {
public:
    /** Instancia del objetivo */
    Objetivo();
    /** Instancia del objetivo en el plano 'plano' en el punto (xp,yp) */
    Objetivo(Frame *frame, Mapa *plano, double xp, double yp);
    ~Objetivo();
    /** El objetivo en el plano 'plano' en el punto (xp,yp) */
    void setObjetivo(Frame *frame, Mapa *plano, double xp, double yp);
    //test del rayo en 2D
    /** Test del rayo en 2D sobre el poligono 'polilinea' */
    bool interior(Polilinea polilinea);
    /** Dibujar el objetivo */
    void dibujar();
    /** Activa el objetivo */
    void activar();
    /** Desactiva el objetivo */
    void desactivar();
    /** Devuelve si el objetivo est&aacute; fijado o no */
    bool getFijado();
    /** Si es v&aacute; o no */
    void setValido(bool valido);
    /** Si es inapropiado */
    bool getValido();
    /** Devuelve la componente X del objetivo */
    double getX();
    /** Devuelve la componente Y del objetivo */
    double getY();
    /** Pregunta si se ha de fijar el objetivo */
    void preguntar();
    /** Devuelve la respuesta dada por el usuario */
    int respuesta(int x, int y);
    /** Devulve si se ha realizado la pregunta */
    bool preguntado();
    /** Se deja de preguntar */
    void nopreguntar();
    /** Carga el objetivo guardado temporalmente */
    void load();
    /** Guarda el objetivo temporalmente */
    void store();
    /** Devuelve el objetivo en formato cadena */
    string toString();
private:
    Frame *frame;
    Mapa *plano;
    double xp,xp_temp;
    double yp,yp_temp;
    float radio;
    bool ofijado,
	 valido,valido_temp,
	 pregunta;
    Boton *bsi,*bno;
};
#endif

