#ifndef FRAME_H
#define FRAME_H
#include <SDL/SDL.h>
#include "boton.h"
#include <iostream>


using namespace std;
/**
 *  \class Frame
 *  \brief Gestiona el sistema de subventanas
 *   
 *  \par 
 */
class Frame  
{
public:
    /** Instancia de frame en la ventana 'ventana' */
    Frame(SDL_Surface *ventana);
    virtual ~Frame();
    /** Carga el frame en la posicion 'x' 'y' con una anchura 'w' y una altura 'h'. El t&iacute;tulo
     * de la ventana es 'c', y el borde de color 'color' */
    void cargarFrame(int x, int y, int w, int h, string c, Uint32 color);
	//void CargarBoton(int x, int y, int w, int h,char *_text, Uint32 _Colorfons, SDL_Color *_Colortext);
   // void cerrarFrame();
   /** Maximiza el frame */
    void maxFrame(int x, int y, int w,int h);
    /** Minimiza el frame */
    void minFrame();
    /** Desactiva el frame */
    void desactivarFrame();
    /** Limpia el frame. Si refresh=true se refresca al momento. */
    void limpiarFrame(bool refresh);
    /** Activa el frame*/
    void activarFrame();
    /** Refresca la zona del frame */
    void refrescarFrame();
    /** Devuelve true si se ha presionado el mouse dentro del frame */
    bool presionado(int xm, int ym);
    /** Devuelve la Surface que contiene al frame */
    SDL_Surface* getVentana();
    /** Devuelve la posici&oacute; X del frame */
    int getX();
    /** Devuelve la posici&oacute; Y del frame */
    int getY();
    /** Devuelve la anchura del frame */
    int getW();
    /** Devuelve la altura del frame */
    int getH();
    /** Devuelve el area del grame */
    SDL_Rect getArea();
    //Boton* getBcerrar();
    /** Devuelve el bot&oacute del frame*/
    Boton* getBmaxmin();
    /** Devuelve el estado del frame */
    Uint8 getEstado();

private:
    string titulo;
    SDL_Rect area,areamax;
    SDL_Surface *ventana;
    SDL_Surface *frame;
    Uint32 color;
    SDL_Rect contenedor,contenedormax;
    //Boton *bcerrar;
    Boton *bmaxmin;
    Uint8 estado;
    int xc,yc;//cordenadas de los campos

};

#endif
