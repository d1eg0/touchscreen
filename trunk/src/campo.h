#ifndef CAMPO_H
#define CAMPO_H
#include <SDL/SDL.h>
#include <string>
#include "boton.h"
#include <iostream>

using namespace std;

class Campo  
{
public:
    Campo(SDL_Surface *surface, 
	    string nombre, 
	    bool estatico,
	    Uint32 colorNombre, 
	    Uint32 colorValor);
    virtual ~Campo();

    void cargarCampo(int x, int y,  Uint32 colorNombre, Uint32 colorValor);
    void recargar();
    void recargar(int x, int y);
    void valorStr(string valor);	
    void valorNum(
	    float valor, 
	    float vmax, 
	    float vmin, 
	    float incremento
	    );	
    void updateValor(float valor);
    void updateValor(string valor);
    void aumentar();
    void disminuir();
    string getVstr();
    //2 mas, 1 menos, 0 ninguno
    int presionado(int x, int y);
    bool handle(int x, int y);


private:
    SDL_Surface *surface;

    string nombre; //etiqueta del campo
    SDL_Rect arean;
    float valor; //valor si es numérico
    string valorstr; //valor si es estático
    bool estatico, //si el campo es estático
	 numerico, //si el campo es numérico
	 modificado; //si ha sido modificado
    SDL_Rect areav;

    float minvalor; //valor mínimo
    float maxvalor; //valor máximo
    float incremento; //valor del incremento

    Uint32 colorNombre; //color de la etiqueta
    Uint32 colorValor; //color del valor


    Boton *bmas; //boton para aumentar
    Boton *bmenos; //boton para disminuir
    Boton *bok; //boton de ok
};

#endif
