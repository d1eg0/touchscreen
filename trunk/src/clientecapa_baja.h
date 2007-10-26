#ifndef CLIENTECAPABAJA_H
#define CLIENTECAPABAJA_H

#include <SolarSockets/SolarSockets++.h>
#include <fstream>
class ClienteCapaBaja : public ssPPClient
{
private:
    void onConnect();
    void onDataArrival(string Data);
    void onError(int ssError);
};
#endif

