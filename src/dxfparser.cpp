#include "dxfparser.h"
#include <iostream>
#include <stdlib.h>
#include "mapa.h"
#include "linea.h"
#include "capa.h"
#include "polilinea.h"
#include "vertice.h"
using namespace std;
extern Mapa plano;
DxfParser::DxfParser(){}

void DxfParser::addLine(const DL_LineData& data) {
    //std::cout << "Line: " << data.x1 << "/" << data.y1
    //<< " " << data.x2 << "/" << data.y2 << std::endl;
    Linea nuevalinea(attributes.getLayer().c_str(),data.x1,data.y1,data.x2,data.y2);
    
    /*int i=0;
    vector<Capa>::iterator i_capa;
    for(i_capa=(*plano.getMapa()).begin(); i_capa!=(*plano.getMapa()).end(); i_capa++){
	 if ((*i_capa).getNombre()==nuevalinea.getCapa()){
	     break;
	 }
	 i++;
    }*/

    //(*plano.getMapa())[i].addLinea(nuevalinea);
    plano.getCapa(nuevalinea.getCapa())->addLinea(nuevalinea);
}

void DxfParser::addLayer(const DL_LayerData& data) {
    //cout << "Capa nueva:"<< data.name << endl;
    Capa nuevacapa(data.name,attributes.getColor());
    plano.addCapa(nuevacapa);
}

void DxfParser::addPolyline(const DL_PolylineData& data) {
    cout << "Polyline:"<< data.number << " flag:" << data.flags << endl;
    bool cerrado;
    if(data.flags==1)cerrado=true;
    else cerrado=false;
    Polilinea nuevapolilinea(data.number,cerrado,attributes.getLayer().c_str());
    /*int i=0;
    vector<Capa>::iterator i_capa;
    for(i_capa=(*plano.getMapa()).begin(); i_capa!=(*plano.getMapa()).end(); i_capa++){
	 if ((*i_capa).getNombre()==attributes.getLayer().c_str()){
	     break;
	 }
	 i++;
    }

    (*plano.getMapa())[i].addPolilinea(polilinea);*/
    plano.getCapa(attributes.getLayer().c_str())->addPolilinea(nuevapolilinea);

}

void DxfParser::addVertex(const DL_VertexData& data) {

    Vertice nuevovertice(data.x,data.y);
    /*int i=0;
    vector<Capa>::iterator i_capa;
    for(i_capa=(*plano.getMapa()).begin(); i_capa!=(*plano.getMapa()).end(); i_capa++){
	 if ((*i_capa).getNombre()==attributes.getLayer().c_str()){
	     break;
	 }
	 i++;
    }
    
    (*plano.getMapa())[i].getPolilinea()->back().addVertice(nuevovertice);*/
    string capa=attributes.getLayer().c_str();
    plano.getCapa(capa)->addVertice(nuevovertice);
    cout <<    "N:" <<plano.getCapa(capa)->getPolilinea()->back().getNum() << endl;
    if (plano.getCapa(capa)->getPolilinea()->back().getNumTotal()==
	    plano.getCapa(capa)->getPolilinea()->back().getNum()){
	cout << "ultimo vertice" << endl;
	vector<Linea> vPolilineas;
	vPolilineas.swap((*plano.getCapa(capa)->getPolilinea()->back().toLineas()));
	plano.getCapa(capa)->clear();	
	vector<Linea>::iterator i_linea;
	for(i_linea=vPolilineas.begin(); i_linea!=vPolilineas.end(); i_linea++){
	    plano.getCapa(capa)->addLinea((*i_linea));
	}
    }
    cout << "\tVertex, capa:" << attributes.getLayer().c_str()<<" x:"<< data.x <<" y:" << data.y << endl;
}

