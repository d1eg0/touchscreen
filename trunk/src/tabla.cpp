#include "tabla.h"

Tabla::Tabla(){
}
Tabla::~Tabla(){
}

void Tabla::add(string n, Campo *c){
    tabla.insert(pair<string,Campo>(n,*c));
   
}

Campo Tabla::get(string n){
    return tabla.find(n)->second;
}

void Tabla::update(string n, string v){
    tabla.find(n)->second.updateValor(v);
    extern ClienteCapaBaja clienteCapaBaja;
    clienteCapaBaja.Send(n+" "+v+"\n\r");
}

void Tabla::update(string n, float v){
    stringstream buffer;
    buffer << v;

    extern ClienteCapaBaja clienteCapaBaja;
    tabla.find(n)->second.updateValor(v);
    clienteCapaBaja.Send(n+" "+buffer.str()+"\n\r");
}

void Tabla::handle(int x,int y){
    map<string, Campo>::iterator it;
    for (it=tabla.begin();it!=tabla.end();it++){
	(*it).second.handle(x,y);
    }
}

void Tabla::recargar(Frame *frame){
    int x=frame->getX();
    int y=frame->getY();
    map<string, Campo>::iterator it;
    for (it=tabla.begin();it!=tabla.end();it++){
	(*it).second.recargar(x+5,y+5);
	y+=20;
    }
    

}
