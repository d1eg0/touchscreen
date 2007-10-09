#include "polilinea.h"

Polilinea::Polilinea(int num, bool cerrado, string capa){
    this->numVertices=num;
    this->cerrado=cerrado;
    this->capa=capa;
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

int Polilinea::getNumTotal(){
    return numVertices;
}

int Polilinea::getNum(){
    return listaVertices.size();
}

vector<Linea>* Polilinea::toLineas(){
    vector<Linea> *vLineas;
    vector<Vertice> parVertices;
    vLineas->clear();
    vector<Vertice>::iterator i_vertice;
    for(i_vertice=listaVertices.begin(); i_vertice!=listaVertices.end(); i_vertice++){
	parVertices.push_back((*i_vertice));
	if(parVertices.size()==2){
cout << "pila\n\tx:" << parVertices.front().getX()<< " y: " << parVertices.front().getY() << endl;
cout << "\tx:" << parVertices.back().getX()<< " y: " << parVertices.back().getY() << endl;
	    Vertice v1(parVertices.front().getX(),parVertices.front().getY()),
		    v2(parVertices.back().getX(),parVertices.back().getY());
	    
	    Linea nuevaLinea(capa,v1.getX(),
		    v1.getY(),
		    v2.getX(),
		    v2.getY());
	    vLineas->push_back(nuevaLinea);
	    parVertices.clear();
	    parVertices.push_back(v2);
	}	
    }
    if (cerrado) {
	cout << "x1: " <<vLineas->front().getX1() <<
		"  y1: " <<vLineas->front().getY1() << 
		"  x2: " <<vLineas->back().getX2() <<
		"  y2: " <<vLineas->back().getY2() <<endl;

	Linea lineaCerrar(capa,
		vLineas->front().getX1(),
		vLineas->front().getY1(),
		vLineas->back().getX2(),
		vLineas->back().getY2());
	vLineas->push_back(lineaCerrar);
    }
    
    return vLineas;
}

