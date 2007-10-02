/**
 *    \file  mapa.cpp
 *   \brief  
 *
 *  Detailed description starts here.
 *
 *  \author  Diego García Valverde , kobydiego@gmail.com
 *
 *  \internal
 *    Created:  26/09/07
 *   Compiler:  gcc/g++
 *    Company:  UIB
 *
 *  This source code is released for free distribution under the terms of the
 *  GNU General Public License as published by the Free Software Foundation.
 * =====================================================================================
 */
#include "mapa.h"

Mapa::Mapa(){
    escala=100;
    ox=0;
    oy=0;
    dh=0;
    dv=0;
}

Mapa::~Mapa(){
    listaCapas.clear();
}

void Mapa::setOrigen(int x, int y){
    ox=x;
    oy=y;
}

double Mapa::getOX(){
    return ox;
}

double Mapa::getOY(){
    return oy;
}

double Mapa::getDH(){
    return dh;
}

double Mapa::getDV(){
    return dv;
}

double Mapa::getEscala(){
    return escala;
}

vector<Capa>* Mapa::getMapa(){
    return &listaCapas;
}

void Mapa::addCapa(Capa capa){
    listaCapas.push_back(capa);
}

void Mapa::clearMapa(){
    listaCapas.clear();
}


void Mapa::pintarMapa(SDL_Surface *screen, Frame *frame, int escala){   
    this->escala=escala;
    this->frame=frame;
    this->pincel=new Dibujar(screen);
    this->calcularDHV(screen,frame);
    this->ox=frame->getX()+dh;
    this->oy=frame->getY()+frame->getH()+dv;
    vector<Capa>::iterator i_capa;
    vector<Linea>::iterator i_linea;
    for(i_capa=this->listaCapas.begin(); i_capa!=this->listaCapas.end(); i_capa++){
	cout << "Capa:" << (*i_capa).getNombre() << "," << (*i_capa).getColor() << ",size:" << (*(*i_capa).getCapa()).size() << endl;
	vector<Linea> llineas=(*(*i_capa).getCapa());
	for(i_linea=llineas.begin(); i_linea!=llineas.end(); i_linea++){
	     Linea linealeida=(*i_linea);
	     //printf("LINE     (%lf, %lf) (%lf, %lf)\n",linealeida.getX1(),linealeida.getY1(), linealeida.getX2(),linealeida.getY2());
	     linealeida.escalar(escala);
	     pincel->dibujarLinea(frame,&linealeida,dh,dv);
	 }
     }
    cout << "ox:" << ox << ", oy:" << oy << endl;
}


void Mapa::calcularDHV(SDL_Surface *screen, Frame *frame){   

    vector<Capa>::iterator i_capa;
    vector<Linea>::iterator i_linea;
    double x_max=0;
    double y_max=0;     
    for(i_capa=this->listaCapas.begin(); i_capa!=this->listaCapas.end(); i_capa++){
	vector<Linea> llineas=(*(*i_capa).getCapa());
	for(i_linea=llineas.begin(); i_linea!=llineas.end(); i_linea++){
	     printf("LINE     (%lf, %lf) (%lf, %lf)\n",(*i_linea).getX1(),(*i_linea).getY1(), (*i_linea).getX2(),(*i_linea).getY2());
	    Linea lleida=(*i_linea);
	    lleida.escalar(escala);
	    if (lleida.getX1()>x_max){
		x_max=lleida.getX1();
	    }
	    if (lleida.getX2()>x_max){
		x_max=lleida.getX2();
	    }
	    if (lleida.getY1()>y_max){
		y_max=lleida.getY1();
	    }
	    if (lleida.getY2()>y_max){
		y_max=lleida.getY2();
	    }
	}
    }
    printf("(Xmax:%lf, Ymax:%lf) --- (Xframe:%d, Yframe:%d)\n",x_max,y_max,frame->getX()+frame->getW(),frame->getY()+frame->getH());
    dh=frame->getW()-x_max;
    dv=frame->getH()-y_max;
    dh*=0.5;
    dv*=-0.5; //negativo porque el eje Y+ apunta a Y-
    printf("Dh:%lf, Dv:%lf\n",dh,dv);

}

/*void Mapa::escalarMapa(int escala){   

    this->escala+=escala;
     vector<Capa>::iterator i_capa;
     vector<Linea>::iterator i_linea;
     for(i_capa=this->listaCapas.begin(); i_capa!=this->listaCapas.end(); i_capa++){
	 vector<Linea> llineas=(*(*i_capa).getCapa());
	 for(i_linea=llineas.begin(); i_linea!=llineas.end(); i_linea++){
	     Linea linealeida=(*i_linea);
	     linealeida.escalar(escala);
	     //printf("LINE     (%lf, %lf) (%lf, %lf)\n",linealeida.getX1(),linealeida.getY1(), linealeida.getX2(),linealeida.getY2());
	     pincel->dibujarLinea(frame,&linealeida, dh, dv);
	 }
     }
}*/

void Mapa::escalarMapa(int escala){
    this->escala+=escala;
    pintarMapa(frame->getVentana(),frame,this->escala);
}










