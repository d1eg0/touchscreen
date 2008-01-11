#ifndef ETIQUETA_H
#define ETIQUETA_H
#include <SDL/SDL.h>



/**
 *  \class Etiqueta
 *  \brief Gestiona etiquetas de texto
 *   
 *  \par 
 */
class Etiqueta  
{
public:
    /** Especificar la "Ventana" donde se situa **/
    Etiqueta(SDL_Surface *Ventana);
    virtual ~Etiqueta();
    /** Carga la etiqueta en la posicion 'x,y' con una anchura 'w' y una altura 'h'. El texto 'c' **/ 
    void cargarEtiqueta(int x, int y, int w, int h, char *c, Uint32 colorFuente, Uint32 colorBorde, Uint32 colorRelleno);
    /** Dibuja la etiqueta con la configuraci&oacute;n inicial **/ 
    void dibujarEtiqueta();
    /** Inserta el texto 'c' en la etiqueta **/ 
    void insertarTexto(char *c);


     

private:
    SDL_Rect area;
    SDL_Rect contenedor;
    SDL_Surface *ventana;

    char *texto;
    Uint32 colorBorde;
    Uint32 colorFuente;
    Uint32 colorRelleno;
	

};

#endif
