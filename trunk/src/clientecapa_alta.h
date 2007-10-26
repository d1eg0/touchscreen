#ifndef CLIENTECAPAALTA_H
#define CLIENTECAPAALTA_H

#include <SolarSockets/SolarSockets++.h>
#include <fstream>
#include <vector>
#include "punto.h"

class ClienteCapaAlta : public ssPPClient
{
public:
    vector<Punto>* getCamino();
private:
    vector<Punto> listaPuntos;
    void onConnect();
    void onDataArrival(string Data);
    void onError(int ssError);
};
#endif

