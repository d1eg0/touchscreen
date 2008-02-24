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
#include "constantes.h"
#include <dxflib/dl_dxf.h>
#include "dxfparser.h"
Mapa::Mapa(){
    this->escala=100;
    this->ox=0;
    this->oy=0;
    this->dh=0;
    this->dv=0;
}

Mapa::~Mapa(){
    listaCapas.clear();
}

void Mapa::lectura(char *ruta){
    //Lectura Fichero DXF, introduce la estructura en plano
    listaCapas.clear();
    DxfParser *parser_dxf=new DxfParser();
    DL_Dxf* dxf = new DL_Dxf();
    if (!dxf->in(ruta, parser_dxf)) {
	std::cerr << "No se ha podido abrir el DXF.\n";
	exit(-1);
    }
    delete dxf;
    delete parser_dxf;
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

char* Mapa::getEscalaStr(){
    char *escala=(char *)malloc(sizeof(int)+sizeof(char));
    sprintf(escala,"%d",(int)this->escala);
    strcat(escala,"\%");
    return escala;
}

vector<Capa>* Mapa::getMapa(){
    return &listaCapas;
}

Capa* Mapa::getCapa(string c){
    int i=0;
    vector<Capa>::iterator i_capa;
    for(i_capa=listaCapas.begin(); i_capa!=listaCapas.end(); i_capa++){
	 if ((*i_capa).getNombre()==c){
	     return &(*i_capa);
	 }
    }
    cerr << "No existe la capa: " << c << endl;
}

void Mapa::addCapa(Capa capa){
    listaCapas.push_back(capa);
}

void Mapa::setCamino(vector<Linea> camino){
    this->camino.clear();
    this->camino=camino;
}
void Mapa::clearMapa(){
    listaCapas.clear();
}


void Mapa::pintarMapa(SDL_Surface *screen, Frame *frame, double escala){   
    this->escala=escala;
    this->frame=frame;
    this->pincel=new Dibujar(screen);
    this->calcularDHV(frame);
    this->ox=frame->getX()+dh;
    this->oy=frame->getY()+frame->getH()+dv;
    vector<Capa>::iterator i_capa;
    vector<Linea>::iterator i_linea;
    frame->limpiarFrame(false);
    for(i_capa=this->listaCapas.begin(); i_capa!=this->listaCapas.end(); i_capa++){
	if((*i_capa).getNombre()!="CapaHabitacions"){
	    vector<Linea> llineas=(*(*i_capa).getCapa());
	    for(i_linea=llineas.begin(); i_linea!=llineas.end(); i_linea++){
		 Punto v1((*i_linea).getX1(),(*i_linea).getY1());
		 Punto v2((*i_linea).getX2(),(*i_linea).getY2());
		 v1.cpantalla(frame,dh,dv,escala);
		 v2.cpantalla(frame,dh,dv,escala);
		 Linea linea((*i_linea).getCapa(),v1,v2);
		 pincel->dibujarLinea(frame,&linea,0x000000ff);
	     }
	}
     }
    this->pintarCamino(screen,frame,escala);
}

void Mapa::pintarCamino(SDL_Surface *screen, Frame *frame, double escala){
    vector<Linea>::iterator i_linea;
    for(i_linea=camino.begin(); i_linea!=camino.end(); i_linea++){
	 Punto v1((*i_linea).getX1(),(*i_linea).getY1());
	 Punto v2((*i_linea).getX2(),(*i_linea).getY2());
	 v1.cpantalla(frame,dh,dv,escala);
	 v2.cpantalla(frame,dh,dv,escala);
	 Linea linea("",v1,v2);
	 pincel->dibujarLinea(frame,&linea,COLORCAMINO);
     }
    frame->refrescarFrame();
}

void Mapa::calcularDHV(Frame *frame){   
    dh=(frame->getW()*0.5-(xm*escala/100.0));
    dv=-(frame->getH()*0.5-(ym*escala/100.0));	//negativo porque el eje Y+ apunta a Y-
}

void Mapa::centrarMapa(){   

    vector<Capa>::iterator i_capa;
    vector<Linea>::iterator i_linea;
    double x_max=0;
    double y_max=0;     
    for(i_capa=this->listaCapas.begin(); i_capa!=this->listaCapas.end(); i_capa++){
	vector<Linea> llineas=(*(*i_capa).getCapa());
	for(i_linea=llineas.begin(); i_linea!=llineas.end(); i_linea++){
	    Linea lleida=(*i_linea);
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
    xm=x_max*0.5;
    ym=y_max*0.5;
}

void Mapa::escalarMapa(double escala){
    this->escala+=escala;
    pintarMapa(frame->getVentana(),frame,this->escala);
}


void Mapa::despArriba(){
    this->ym+=FACTOR_DESP;
    pintarMapa(frame->getVentana(),frame,this->escala);
}

void Mapa::despAbajo(){
    this->ym-=FACTOR_DESP;
    pintarMapa(frame->getVentana(),frame,this->escala);
}

void Mapa::despIzquierda(){
    this->xm-=FACTOR_DESP;
    pintarMapa(frame->getVentana(),frame,this->escala);
}

void Mapa::despDerecha(){
    this->xm+=FACTOR_DESP;
    pintarMapa(frame->getVentana(),frame,this->escala);
}




