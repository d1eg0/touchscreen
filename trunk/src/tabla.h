#ifndef TABLA_H
#define TABLA_H
#include <map>
#include <utility>
#include <string>
#include "campo.h"
#include "frame.h"
#include <iostream>
#include "clientecapa_alta.h"
using namespace std;

/**
 *  \class Tabla
 *  \brief tabla compuesta por elementos de clase Campo
 *   
 *  \par 
 */
class Tabla{
public:
    Tabla();
    ~Tabla();

    /** Añadir un campo a la tabla con la etiqueta unica 'n' */
    void add(string n,Campo *c);

    /** Devuelve el campo con la etiqueta 'n' */
    Campo get(string n);

    /** Cambia el valor del campo con la etiqueta 'n' por el valor string 'v'*/
    void update(string n, string v);

    /** Cambia el valor del campo con la etiqueta 'n' por el valor float 'v'*/
    void update(string n, float v);

    /** Gestiona el input de la pantalla tactil */
    void handle(int x, int y);

    /** Recarga la tabla en el Frame 'frame' */
    void recargar(Frame *frame);

private:
    map<string, Campo> tabla;


};
#endif
