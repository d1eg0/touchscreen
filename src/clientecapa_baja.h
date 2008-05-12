#ifndef CLIENTECAPABAJA_H
#define CLIENTECAPABAJA_H

#include <SolarSockets/SolarSockets++.h>
#include <fstream>
#include <vector>
#include <SDL/SDL_thread.h>
#include <sstream>
#include <iostream>
#include "punto.h"
using namespace std;
/**
 *  \class ClienteCapaBaja
 *  \brief gestiona la conexion con el embedded IA
 *   
 *  \par 
 */
class ClienteCapaBaja : public ssPPClient
{
public:
    /** devuelve los valores obtenidos */
    vector<double> getValores();
private:
    vector<double> listaValores;
    Punto pos;
    double angulo;
    double sensor[4];
    void onConnect();
    //void onDataArrival(string Data);
    void onLineArrival(string Cadena);
    void onClose();
    void onError(int ssError);
};
#endif

