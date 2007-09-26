#include "dxfparser.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

DxfParser::DxfParser(){}

void DxfParser::addLine(const DL_LineData& data) {
    std::cout << "Line: " << data.x1 << "/" << data.y1
    << " " << data.x2 << "/" << data.y2 << std::endl;
    cout << "Capa:" << attributes.getLayer().c_str() << endl;
}

void DxfParser::addLayer(const DL_LayerData& data) {
    cout << "Capa nueva:"<< data.name << endl;
}

