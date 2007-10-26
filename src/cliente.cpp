#include <SolarSockets/SolarSockets++.h>
#include <fstream>
#include "cliente.h"

void Cliente::onConnect()
  {

	cout << this->getStatus() << endl;
	while(this->getStatus()==1001){}
	cout << "Conectado :)" << endl;
	//Send("***te mando el fichero\n\r");
  }
  void Cliente::onDataArrival(string Data)
  {
    cout << "Datos:" << Data << endl;
  }
  void Cliente::onError(int ssError){
      cout << ssError <<":Error de conexion***********" << endl;
  }



