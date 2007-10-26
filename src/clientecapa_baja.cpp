#include <SolarSockets/SolarSockets++.h>
#include <fstream>
#include "clientecapa_baja.h"

void ClienteCapaBaja::onConnect()
{
    //cout << this->getStatus() << endl;
    while(this->getStatus()==1001){}//Esperar la conexion

}
void ClienteCapaBaja::onDataArrival(string Data)
{
cout << "Datos:" << Data << endl;
}
void ClienteCapaBaja::onError(int ssError){
  cerr << ssError <<":Error de conexion" << endl;
}



