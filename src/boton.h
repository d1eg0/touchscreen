/**
 *       @file  boton.h
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


#ifndef BOTON_H
#define BOTON_H
#include <SDL/SDL.h>
#include <iostream>
using namespace std;

/**
 *  \class Boton
 *  \brief Gestiona la entidad bot&oacute;n
 *   
 *  \par 
 */
/** El bot&oacute; puede estar el estado: activo o inactivo */
enum EstadoBoton {activo=1,inactivo=0,z=3};
class Boton  
{
public:
    /** Constructor, se ha de indicar donde sera pintado -> Ventana */
    Boton(SDL_Surface *Ventana);
    virtual ~Boton();
    /** visualizar el boton en la posicion (x,y) y con una dimension de (w x h) = ancho x alto */
    void cargarBoton(int x, int y, int w, int h, string c, Uint32 colorFondo,Uint32 colorBorde);
    /** para visualizar el boton en caso de haber sido borrado */
    void recargarBoton();
    /** devuelve true si el boton esta presionado, false en caso contrario */ 
    bool presionado(int xm, int ym);
    /** devuelve el estado del boton, true=activo false=inactivo */
    bool getEstado();
    /** devuelve el texto del boton */
    string getTexto();
    /** desactiva el boton, pero se sigue visualizando */
    void desactivar();     
    /** deshabilita el boton, oscurenciendolo */
    void deshabilitar();     
    /** borra el boton */
    void borrar();
    /** poner icono */
    void setIcono(string iconoruta);
private:
    SDL_Rect area;
    SDL_Surface *ventana;
    string texto;
    Uint32 colorFondo;
    Uint32 colorBorde;

    SDL_Surface *surfacef;
    SDL_Color colorFuente;
    int Sizef;
    SDL_Rect contenedor;
    
    SDL_Surface *icono;
    string iconopath;
    bool conicono; 
    EstadoBoton estado;
};

#endif
