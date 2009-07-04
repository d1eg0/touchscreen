/**
 *       @file  radar.h
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

#include "punto.h"
#include "frame.h"
#include <vector>
#include <SDL/SDL_thread.h>
using namespace std;

/**
 *  \class Radar
 *  \brief El radar indica los obst&aacute;culos pr&oacute;ximos y la orientaci&oacute;n de la silla.
 *   
 *  \par 
 */

class Radar{
public:
    /** Instancia del radar */
    Radar(Frame *frame);
    ~Radar();
    /** Recarga el radar, 'refresh' a true si se precisa refrescar */
    void recargar(bool refresh);
    /** Devuelve la componente X del radar */
    int getX();
    /** Devuelve la componente Y del radar */
    int getY();
    /** Devuelve el radio de la circunferencia m&aacute;s peque&ntilde;a */
    int getR1();
    /** Devuelve el radio de la circunferencia mediana */
    int getR2();
    /** Devuelve el radio de la circunferencia m&aacute;s grande */
    int getR3();
    /** Devuelve el frame que contiene el radar */
    Frame *getFrame();
    /** Devuelve la lista de obst&aacute;culos */
    vector<Punto> getObstaculos();
    /** A&ntilde;adir un nuevo punto 'o' */
    void addObstaculo(Punto o);
    /** Dibuja la flecha que indica la rotaci&oacute;n de la silla */
    void dibujarFlecha(int rot);
    /** Devuelve el Surface donde se pinta la flecha */
    SDL_Surface *getFlecha();
    /** Devuelve el desplazamiento */
    SDL_Rect getDesp();
private:
    SDL_Thread *s;
    vector<Punto> lobstaculos;
    Frame* frame;
    int xm,
	ym;
    Uint32 color;
    int r[3];
    SDL_Rect desp;
    int rot;
    SDL_Surface *flecha;
};
