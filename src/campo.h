#ifndef CAMPO_H
#define CAMPO_H
#include <SDL/SDL.h>
#include <string>
#include "boton.h"
#include <iostream>

/**
 *  \class Campo
 *  \brief crear campos estaticos o numericos y dinamicos
 *   
 *  \par 
 */
using namespace std;

class Campo  
{
public:
    /** constructor, 'surface' donde se dibuja, 'nombre' etiqueta del campo, 'estatico' true->estatico y false->dinamico,
     * 'colorNombre' color de la etiqueta, 'colorValor' color del valor */
    Campo(SDL_Surface *surface, 
	    string nombre, 
	    bool estatico,
	    Uint32 colorNombre, 
	    Uint32 colorValor);
    virtual ~Campo();

    /** carga el campo en la posicion 'x' 'y' con la etiqueta de color 'colorNombre' y con el valor de color 'colorValor' */
    void cargarCampo(int x, int y,  Uint32 colorNombre, Uint32 colorValor);
    /** recarga el campo en su posion inicial */
    void recargar();
    /** recarga el campo en la posion 'x' 'y' */
    void recargar(int x, int y);
    /** el campo tendra el valor de tipo string (en este caso no puede ser dinamico)*/
    void valorStr(string valor);	
    /** el campo tendra el valor de tipo float con un valor maximo 'vmax', un valor minimo 'vmin'
     * y un incremento 'incremento' (solo si es dinamico) */
    void valorNum(
	    float valor, 
	    float vmax, 
	    float vmin, 
	    float incremento
	    );	
    /** actuliza el valor de tipo float*/
    void updateValor(float valor);
    /** actualiza el valor de tipo string*/
    void updateValor(string valor);
    /** aumenta el valor (si es dinamico) una cantidad 'incremento' */
    void aumentar();
    /** disminuye el valor (si es dinamico) una cantidad 'incremento' */
    void disminuir();
    /** devuelve el valor actual del campo en formato string*/
    string getVstr();
    /** devuelve true si se ha presionado ok */ 
    bool handle(int x, int y);


private:
    /** devuelve que boton ha sido presionado-> 2 mas, 1 menos, 0 ninguno */
    int presionado(int x, int y);
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
