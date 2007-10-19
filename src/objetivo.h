#ifndef OBJETIVO_H
#define OBJETIVO_H
#include "polilinea.h"
#include "frame.h"
class Objetivo {
public:
    Objetivo(Frame *frame,double xp, double yp);
    ~Objetivo();
    //test del rayo en 2D
    bool interior(Polilinea polilinea);
    void dibujar(int x, int y, bool zvalida);
private:
    Frame *frame;
    double xp;
    double yp;
    int radio;
};
#endif

