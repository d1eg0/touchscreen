#ifndef OBJETIVO_H
#define OBJETIVO_H
#include "polilinea.h"
#include "frame.h"
class Objetivo {
public:
    Objetivo();
    Objetivo(Frame *frame,double xp, double yp);
    ~Objetivo();
    void setObjetivo(Frame *frame,double xp, double yp);
    //test del rayo en 2D
    bool interior(Polilinea polilinea);
    void dibujar(int x, int y, bool zvalida);
    void desactivar();
    bool activado();
    double getX();
    double getY();
private:
    Frame *frame;
    double xp;
    double yp;
    int radio;
    bool activo,
	 valido;
};
#endif

