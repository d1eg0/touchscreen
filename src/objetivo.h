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
    void dibujar();
    void activar();
    void desactivar();
    bool getFijado();
    void setValido(bool valido);
    bool getValido();
    double getX();
    double getY();
    void preguntar();
    int respuesta(int x, int y);
    bool preguntado();
    void nopreguntar();
    void load();
    void store();
private:
    Frame *frame;
    Mapa *plano;
    double xp,xp_temp;
    double yp,yp_temp;
    float radio;
    bool ofijado,
	 valido,
	 pregunta;
    Boton *bsi,*bno;
};
#endif

