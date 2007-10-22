#include "polilinea.h"

Polilinea::Polilinea(int num, bool cerrado, string capa){
    this->numVertices=num;
    this->cerrado=cerrado;
    this->capa=capa;
}

Polilinea::~Polilinea(){
    listaVertices.clear();
}

vector<Punto>* Polilinea::getPolilinea(){
    return &listaVertices;
}

void Polilinea::addVertice(Punto vertice){
    listaVertices.push_back(vertice);
}

bool Polilinea::getCerrado(){
    return cerrado;
}

int Polilinea::getNumTotal(){
    return numVertices;
}

int Polilinea::getNum(){
    return listaVertices.size();
}

vector<Linea> Polilinea::toLineas(){
    vector<Linea> vLineas;
    vector<Punto> parVertices;
    vLineas.clear();
    vector<Punto>::iterator i_vertice;
    for(i_vertice=listaVertices.begin(); i_vertice!=listaVertices.end(); i_vertice++){
	parVertices.push_back((*i_vertice));
	if(parVertices.size()==2){
	    Punto v1(parVertices.front().getX(),parVertices.front().getY()),
		    v2(parVertices.back().getX(),parVertices.back().getY());
	    
	    Linea nuevaLinea(capa,v1.getX(),
		    v1.getY(),
		    v2.getX(),
		    v2.getY());
	    vLineas.push_back(nuevaLinea);
	    parVertices.clear();
	    parVertices.push_back(v2);
	}	
    }
    if (cerrado) {
	Linea lineaCerrar(capa,
		vLineas.front().getX1(),
		vLineas.front().getY1(),
		vLineas.back().getX2(),
		vLineas.back().getY2());
	vLineas.push_back(lineaCerrar);
    }
    
    return vLineas;
}

