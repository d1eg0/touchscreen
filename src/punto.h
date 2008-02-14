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
    /** Instancia de un punto */
    Punto();
    /** Instancia de un punto (x,y) */
    Punto(double x, double y);
    ~Punto();
    /** Devuelve la componente X del punto */
    double getX();
    /** Devuelve la componente Y del punto */
    double getY();
    /** Cambiar sistema cordenadas de plano a  pantalla */
    void cpantalla(Frame *frame, double dh, double dv,double escala);
    /** Cambiar sistema cordenadas de pantalla a plano */
    void cplano(double x, double y, double escala, double ox, double oy);

private:
    double x,y; 
    //string capa;
};
#endif

