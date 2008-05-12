#ifndef CLIENTECAPAALTA_H
#define CLIENTECAPAALTA_H

#include <SolarSockets/SolarSockets++.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "punto.h"


/**
 *  \class ClienteCapaAlta
 *  \brief Socket que escucha el camino cuando se pida un objetivo
 *   
 *  \par 
 */
class ClienteCapaAlta : public ssPPClient
{
public:
    /** Obtiene el camino guardado */
    vector<Punto> getCamino();
    /** Borra el camino guardado */
    void clearCamino();
    void enviar(string path);
private:
    string modo;
    double status;
    stringstream buffer;
    vector<Punto> listaPuntos;
    void onConnect();
    void onClose();
    void onLineArrival(string Cadena);
    void onError(int ssError);
};
#endif

