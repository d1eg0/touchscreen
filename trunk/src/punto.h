#ifndef Punto_H
#define Punto_H

#include <dxflib/dl_dxf.h>
#include "frame.h"
/**
 *  \class Punto
 *  \brief Punto de un polyline
 *   
 *  \par 
 */
class Punto {
public:
    Punto();
    Punto(double x, double y);
    ~Punto();
    double getX();
    double getY();
    //cordenadas plano a cordenadas pantalla
    void transformar(Frame *frame, double dh, double dv,double escala);
    //string getCapa();
    //void escalar(double escala);
private:
    double x,y; 
    //string capa;
};
#endif

