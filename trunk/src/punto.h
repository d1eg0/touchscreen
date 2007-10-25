#ifndef PUNTO_H
#define PUNTO_H

#include <dxflib/dl_dxf.h>
#include "frame.h"
//#include "mapa.h"
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
    //Cambiar sistema cordenadas
    //de plano a  pantalla
    void cpantalla(Frame *frame, double dh, double dv,double escala);
    //de pantalla a plano
    void cplano(double x, double y, double escala, double ox, double oy);

private:
    double x,y; 
    //string capa;
};
#endif

