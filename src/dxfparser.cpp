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
    Linea nuevalinea(attributes.getLayer().c_str(),data.x1,data.y1,data.x2,data.y2);
    
    plano.getCapa(nuevalinea.getCapa())->addLinea(nuevalinea);
}

void DxfParser::addLayer(const DL_LayerData& data) {
    Capa nuevacapa(data.name,attributes.getColor());
    plano.addCapa(nuevacapa);
}

void DxfParser::addPolyline(const DL_PolylineData& data) {
    bool cerrado;
    if(data.flags==1)cerrado=true;
    else cerrado=false;
    Polilinea nuevapolilinea(data.number,cerrado,attributes.getLayer().c_str());

    plano.getCapa(attributes.getLayer().c_str())->addPolilinea(nuevapolilinea);
}

void DxfParser::addVertex(const DL_VertexData& data) {

    Vertice nuevovertice(data.x,data.y);
    string capa=attributes.getLayer().c_str();
    plano.getCapa(capa)->addVertice(nuevovertice);
    if (plano.getCapa(capa)->getPolilinea()->back().getNumTotal()==
	    plano.getCapa(capa)->getPolilinea()->back().getNum()){
	vector<Linea> vPolilineas;
	vPolilineas.swap((*plano.getCapa(capa)->getPolilinea()->back().toLineas()));
	plano.getCapa(capa)->clear();	
	vector<Linea>::iterator i_linea;
	for(i_linea=vPolilineas.begin(); i_linea!=vPolilineas.end(); i_linea++){
	    plano.getCapa(capa)->addLinea((*i_linea));
	}
    }
}

