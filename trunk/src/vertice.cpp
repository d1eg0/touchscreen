#include "vertice.h"

using namespace std;

Vertice::Vertice(double x, double y){
    //this->capa=capa;
    this->x=x;
    this->y=y;
}

Vertice::~Vertice(){
}


double Vertice::getX(){
    return x;
}
double Vertice::getY(){
    return y;
}

/*string Vertice::getCapa(){
    return capa;
}*/

/*void Vertice::escalar(double escala){
    if (escala>500||escala<0)
	cerr<<"Error: escala incorrecta"<<endl;
    else{
	double factor=100.0/escala;
	this->x1/=factor;
	this->y1/=factor;
	this->x2/=factor;
	this->y2/=factor;
    }

}*/
