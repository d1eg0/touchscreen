/**
 *       @file  mapa.cpp
 *
 *     @author  Diego García , kobydiego@gmail.com
 *
 *   @internal
 *     Company  Universitat de les Illes Balears
 *   Copyright  Copyright (c) 2009, Diego García
 *
 *
 *  This file is part of TouchScreenGUI.
 *  TouchScreenGUI is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  TouchScreenGUI is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TouchScreenGUI; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  http://www.gnu.org/copyleft/gpl.html
 *
 * =====================================================================================
 */

#include "mapa.h"
#include "constantes.h"
#include <dxflib/dl_dxf.h>
#include "dxfparser.h"
#include <math.h>
Mapa::Mapa(){
    this->escala=100;
    //this->ox=0;
    //this->oy=0;
    this->dh=0;
    this->dv=0;
}

Mapa::~Mapa(){
    listaCapas.clear();
    camino.clear();
}

void Mapa::lectura(string ruta){
    //Lectura Fichero DXF, introduce la estructura en plano
    path=ruta;
    listaCapas.clear();
    camino.clear();
    DxfParser *parser_dxf=new DxfParser();
    DL_Dxf* dxf = new DL_Dxf();
    if (!dxf->in(ruta.c_str(), parser_dxf)) {
	std::cerr << "No se ha podido abrir el DXF.\n";
	exit(-1);
    }
    delete dxf;
    delete parser_dxf;
}

string Mapa::getPath(){
    return path;
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
    Capa *vacia=new Capa();
    return vacia;
}

void Mapa::addCapa(Capa capa){
    listaCapas.push_back(capa);
}

void Mapa::setCamino(vector<Linea> camino){
    this->camino.clear();
    this->camino=camino;
}
void Mapa::clearCamino(){
    this->camino.clear();
}
void Mapa::clearMapa(){
    listaCapas.clear();
}


void Mapa::pintarMapa(SDL_Surface *screen, double escala){   
    this->escala=escala;
    this->pincel=new Dibujar(screen);
    this->calcularDHV(frame);
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
    dv=(frame->getH()*0.5-(ym*escala/100.0));	//negativo porque el eje Y+ apunta a Y-
}
void Mapa::calcularZoom(){

    this->calcularDHV(frame);
    vector<Capa>::iterator i_capa;
    vector<Linea>::iterator i_linea;
    int margen=4;
    double x_max=0;
    double y_max=0;     
    double x_min=0;
    double y_min=0;     
    double fx,fy,f;
    double x_mayor,y_mayor;
    for(i_capa=this->listaCapas.begin(); i_capa!=this->listaCapas.end(); i_capa++){
	vector<Linea> llineas=(*(*i_capa).getCapa());
	for(i_linea=llineas.begin(); i_linea!=llineas.end(); i_linea++){
	    Linea lleida=(*i_linea);
	    if (fabs(lleida.getX1())>x_max){x_max=lleida.getX1();}
	    if (fabs(lleida.getX2())>x_max){x_max=lleida.getX2();}
	    if (fabs(lleida.getY1())>y_max){y_max=lleida.getY1();}
	    if (fabs(lleida.getY2())>y_max){y_max=lleida.getY2();}
	}
    }
    fx=dh/(x_max+margen);
    fy=dv/(y_max+margen);
    if(fx<fy)f=fx;
    else f=fy;
    int e=(int)floor(f*100.0);
    escala=e-fmod(e,FACTOR_ZOOM);
    escalaOptima=escala;

}

void Mapa::centrarMapa(){   
    xm=0;
    ym=0;
}

void Mapa::escalarMapa(double escala){
    this->escala+=escala;
    pintarMapa(frame->getVentana(),this->escala);
}


void Mapa::despArriba(){
    this->ym+=FACTOR_DESP;
    pintarMapa(frame->getVentana(),this->escala);
}

void Mapa::despAbajo(){
    this->ym-=FACTOR_DESP;
    pintarMapa(frame->getVentana(),this->escala);
}

void Mapa::despIzquierda(){
    this->xm-=FACTOR_DESP;
    pintarMapa(frame->getVentana(),this->escala);
}

void Mapa::despDerecha(){
    this->xm+=FACTOR_DESP;
    pintarMapa(frame->getVentana(),this->escala);
}

void Mapa::setFrame(Frame *frame){
    this->frame=frame;
}


