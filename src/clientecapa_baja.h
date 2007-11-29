#ifndef CLIENTECAPABAJA_H
#define CLIENTECAPABAJA_H

#include <SolarSockets/SolarSockets++.h>
#include <fstream>
#include <vector>
#include <SDL/SDL_thread.h>
#include <sstream>
#include <iostream>

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
    void onConnect();
    void onDataArrival(string Data);
    void onError(int ssError);
};
#endif

