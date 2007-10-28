#include <SolarSockets/SolarSockets++.h>
#include <fstream>
#include "clientecapa_alta.h"
#include "campo.h"
extern Campo *c1;
void ClienteCapaAlta::onConnect()
{
    //cout << this->getStatus() << endl;
    while(this->getStatus()==1001){}//Esperar la conexion
    //c1->updateValor(3);
    ifstream::pos_type size;
    char * memblock;
    ifstream myFile ("maps/modelo.dxf", ios::in|ios::binary|ios::ate );
    if (myFile.is_open()){
	size = myFile.tellg();
	memblock=new char[size];
	myFile.seekg (0, ios::beg);
	myFile.read (memblock, size);
	myFile.close();
	Send(memblock,size);
    }else cerr << "Error: No se puede abrir el fichero" << endl;

    //cout << "Conectado :)" << endl;
    //Send("***te mando el fichero\n\r");
}
void ClienteCapaAlta::onDataArrival(string Data)
{
    cout << "Datos:" << Data << endl;   
    string coord=Data;
    size_t pos;
    pos=coord.find_first_of(" ");
    while (pos!=string::npos)
    {	
	pos=coord.find_first_of(" ",pos+1);	
    }
}
void ClienteCapaAlta::onError(int ssError){
  cerr << ssError <<":Error de conexion" << endl;
}


vector<Punto>* ClienteCapaAlta::getCamino(){
    return &listaPuntos;
}

