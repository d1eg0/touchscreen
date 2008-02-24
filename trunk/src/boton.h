#ifndef BOTON_H
#define BOTON_H
#include <SDL/SDL.h>
#include <string>
/**
 *    \file  boton.h
 *   \brief  
 *
 *  Crear botones
 *
 *  \author  Diego García Valverde , kobydiego@gmail.com
 *
 *  \internal
 *    Created:  29/11/07
 *   Compiler:  gcc/g++
 *    Company:  UIB
 *
 *  This source code is released for free distribution under the terms of the
 *  GNU General Public License as published by the Free Software Foundation.
 * =====================================================================================
 */



/**
 *  \class Boton
 *  \brief Gesti&oacute;n de botones
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
    void cargarBoton(int x, int y, int w, int h, char *c, Uint32 color);
    /** para visualizar el boton en caso de haber sido borrado */
    void recargarBoton();
    /** devuelve true si el boton esta presionado, false en caso contrario */ 
    bool presionado(int xm, int ym);
    /** devuelve el estado del boton, true=activo false=inactivo */
    bool getEstado();
    /** devuelve el texto del boton */
    char* getTexto();
    /** desactiva el boton, pero se sigue visualizando */
    void desactivar();     
    /** deshabilita el boton, oscurenciendolo */
    void deshabilitar();     
    /** borra el boton */
    void borrar();
    /** poner icono */
    void setIcono(char* iconoruta);
private:
    SDL_Rect area;
    SDL_Surface *ventana;
    char *texto;
    Uint32 color;

    SDL_Surface *surfacef;
    SDL_Color colorFuente;
    int Sizef;
    SDL_Rect contenedor;
    
    SDL_Surface *icono;
    char *iconopath;
    bool conicono; 
    EstadoBoton estado;
};

#endif
