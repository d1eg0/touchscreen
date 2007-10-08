#include "polilinea.h"

Polilinea::Polilinea(int num, bool cerrado){
    this->numLineas=num;
    this->cerrado=cerrado;
}

Polilinea::~Polilinea(){
    listaVertices.clear();
}

vector<Vertice>* Polilinea::getPolilinea(){
    return &listaVertices;
}

void Polilinea::addVertice(Vertice vertice){
    listaVertices.push_back(vertice);
}

bool Polilinea::getCerrado(){
    return cerrado;
}

int Polilinea::getNumlineas(){
    return numLineas;
}
