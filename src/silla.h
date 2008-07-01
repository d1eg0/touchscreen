#ifndef SILLA_H
#define SILLA_H
#include "punto.h"
#include "frame.h"
#include "mapa.h"

/**
 *  \class Silla
 *  \brief Gestiona la posicion y orientacion de la silla
 *   
 *  \par 
 */
class Silla{
private:
    Punto pos;
    int radio;
    int rot;
    int status;
    Frame *frame;
    Mapa *plano;
public:
    /** Crear una silla en el Frame 'frame' en el Mapa 'plano' */
    Silla(Frame *frame, Mapa *plano);
    ~Silla();
    
    /** Devuelve la posicion de la silla */
    Punto getPos();

    /** Actualiza la posicion actual al punto 'pos' */
    void setPos(Punto pos);

    /** Devuelve la rotacion 0-360 */
    int getRot();

    /** Actualiza la rotacion actual a 'r' */
    void setRot(int r);
    void toogleStatus();
    int getStatus();

    /** Dibuja la silla en la posicion correspondiente */
    void dibujar();

};
#endif
