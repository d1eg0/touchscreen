#ifndef OBJETIVO_H
#define OBJETIVO_H
#include "polilinea.h"
#include "frame.h"
#include "mapa.h"
#include "boton.h"
class Objetivo {
public:
    Objetivo();
    Objetivo(Frame *frame, Mapa *plano, double xp, double yp);
    ~Objetivo();
    void setObjetivo(Frame *frame, Mapa *plano, double xp, double yp);
    //test del rayo en 2D
    bool interior(Polilinea polilinea);
    void dibujar(bool zvalida);
    void activar();
    void desactivar();
    bool getFijado();
    bool getValido();
    double getX();
    double getY();
    void preguntar();
    int responder(int x, int y);
    bool preguntado();
    void respondido();
private:
    Frame *frame;
    Mapa *plano;
    double xp;
    double yp;
    float radio;
    bool ofijado,
	 valido,
	 pregunta;
    Boton *bsi,*bno;
};
#endif

