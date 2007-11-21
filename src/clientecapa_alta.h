#ifndef CLIENTECAPAALTA_H
#define CLIENTECAPAALTA_H

#include <SolarSockets/SolarSockets++.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "punto.h"

class ClienteCapaAlta : public ssPPClient
{
public:
    vector<Punto> getCamino();
    void clearCamino();
private:
    stringstream buffer;
    vector<Punto> listaPuntos;
    void onConnect();
    void onClose();
    //void onDataArrival(string Data);
    //void onDataArrival(const char* Cadena, unsigned int Length);
    void onLineArrival(string Cadena);
    void onError(int ssError);
};
#endif

