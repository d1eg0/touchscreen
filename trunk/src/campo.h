#ifndef CAMPO_H
#define CAMPO_H
#include <SDL/SDL.h>
#include <string>
#include "boton.h"

using namespace std;

class Campo  
{
public:
    Campo(SDL_Surface *surface, 
	    string nombre, 
	    bool estatico);
    virtual ~Campo();

    void cargarCampo(int x, int y,  Uint32 colorNombre, Uint32 colorValor);
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
    int presionado(int x, int y);


private:
    SDL_Surface *surface;

    string nombre;
    SDL_Rect arean;
    float valor;
    string valorstr;
    bool estatico,
	 numerico;
    SDL_Rect areav;

    float minvalor;
    float maxvalor;
    float incremento;

    Uint32 colorNombre;
    Uint32 colorValor;


    Boton *bmas;
    Boton *bmenos;
};

#endif
