#ifndef OBJETIVO_H
#define OBJETIVO_H
#include "polilinea.h"
class Objetivo {
public:
    Objetivo(double xp, double yp);
    ~Objetivo();
    //test del rayo en 2D
    bool interior(Polilinea polilinea);
private:
    double xp;
    double yp;
};
#endif

