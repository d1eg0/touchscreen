#ifndef VERTICE_H
#define VERTICE_H

#include <dxflib/dl_dxf.h>

/**
 *  \class Vertice
 *  \brief vertice de un polyline
 *   
 *  \par 
 */
class Vertice {
public:
    Vertice();
    Vertice(double x, double y);
    ~Vertice();
    double getX();
    double getY();
    //string getCapa();
    //void escalar(double escala);
private:
    double x,y; 
    //string capa;
};
#endif

