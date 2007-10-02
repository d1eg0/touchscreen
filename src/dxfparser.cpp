#include "dxfparser.h"
#include <iostream>
#include <stdlib.h>
#include "mapa.h"
#include "linea.h"
#include "capa.h"
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

