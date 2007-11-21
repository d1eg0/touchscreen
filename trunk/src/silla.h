#ifndef SILLA_H
#define SILLA_H
#include "punto.h"
#include "frame.h"
#include "mapa.h"
class Silla{
private:
    Punto pos;
    int radio;
    int rot;
    Frame *frame;
    Mapa *plano;
public:
    Silla(Frame *frame, Mapa *frame);
    ~Silla();
    Punto getPos();
    void setPos(Punto pos);
    void dibujar();

};
#endif
