#ifndef CLIENTECAPAALTA_H
#define CLIENTECAPAALTA_H

#include <SolarSockets/SolarSockets++.h>
#include <fstream>
#include <vector>
#include "punto.h"

class ClienteCapaAlta : public ssPPClient
{
public:
    vector<Punto> getCamino();
    volatile float valor;
private:
    vector<Punto> listaPuntos;
    void onConnect();
    void onDataArrival(string Data);
    void onDataArrival(const char* Data, unsigned int Length);
    void onError(int ssError);
    float getValor();
};
#endif

