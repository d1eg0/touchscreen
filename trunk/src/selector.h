#ifndef SELECTOR_H
#define SELECTOR_H
#include <string>
#include <vector>
#include <SDL/SDL.h>
#include "boton.h"
using namespace std;
class Selector{


public:
    Selector(SDL_Surface* pantalla);
    ~Selector();
    void buscar(string ruta,string ext);
    void cargar();
    bool handle(int x,int y);
private:
    vector<Boton> lista;
    SDL_Surface* ventana;
    string ruta;
    string ext;
    vector<string> mapas;
};
#endif
