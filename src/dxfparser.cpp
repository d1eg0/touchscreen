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
    
    int i=0;
    vector<Capa>::iterator i_capa;
    for(i_capa=(*plano.getMapa()).begin(); i_capa!=(*plano.getMapa()).end(); i_capa++){
	 if ((*i_capa).getNombre()==nuevalinea.getCapa()){
	     break;
	 }
	 i++;
    }

    (*plano.getMapa())[i].addLinea(nuevalinea);
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
    Polilinea polilinea(data.number,cerrado);
    int i=0;
    vector<Capa>::iterator i_capa;
    for(i_capa=(*plano.getMapa()).begin(); i_capa!=(*plano.getMapa()).end(); i_capa++){
	 if ((*i_capa).getNombre()==attributes.getLayer().c_str()){
	     break;
	 }
	 i++;
    }

    (*plano.getMapa())[i].addPolilinea(polilinea);

}

void DxfParser::addVertex(const DL_VertexData& data) {

    Vertice nuevovertice(data.x,data.y);
    int i=0;
    vector<Capa>::iterator i_capa;
    for(i_capa=(*plano.getMapa()).begin(); i_capa!=(*plano.getMapa()).end(); i_capa++){
	 if ((*i_capa).getNombre()==attributes.getLayer().c_str()){
	     break;
	 }
	 i++;
    }

    (*plano.getMapa())[i].getPolilinea()->back().addVertice(nuevovertice);
    cout << "\tVertex, capa:" << attributes.getLayer().c_str()<<" x:"<< data.x <<" y:" << data.y << endl;
}

