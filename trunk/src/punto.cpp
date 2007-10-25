#include "punto.h"

using namespace std;

Punto::Punto(){
}
Punto::Punto(double x, double y){
    //this->capa=capa;
    this->x=x;
    this->y=y;
}

Punto::~Punto(){
}


double Punto::getX(){
    return x;
}
double Punto::getY(){
    return y;
}

void Punto::cpantalla(Frame *frame, double dh, double dv,double escala){
    double factor=escala/100.0;
    this->y*=factor;
    this->x*=factor;
    this->y= (frame->getH()+frame->getY())-this->y+dv;
    this->x= frame->getX()+this->x+dh;

}

void Punto::cplano(double x, double y, double escala, double ox, double oy){
    double factor=100.0/escala;
    this->x=(x-ox)*factor;
    this->y=(-y+oy)*factor;
}
/*string Punto::getCapa(){
    return capa;
}*/

/*void Punto::escalar(double escala){
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
