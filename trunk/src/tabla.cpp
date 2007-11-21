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

void Tabla::update(string n, string v, bool enviar){
    tabla.find(n)->second.updateValor(v);
/*    if(enviar){
	extern ClienteCapaBaja clienteCapaBaja;
	clienteCapaBaja.Send(n+" "+v+"\n\r");
    }*/
}

void Tabla::update(string n, float v, bool enviar){
    stringstream buffer;
    buffer << v;

    tabla.find(n)->second.updateValor(v);
/*    if(enviar){
	extern ClienteCapaBaja clienteCapaBaja;
	clienteCapaBaja.Send(n+" "+buffer.str()+"\n\r");
    }*/
}

void Tabla::handle(int x,int y){
    map<string, Campo>::iterator it;
    for (it=tabla.begin();it!=tabla.end();it++){
	if((*it).second.handle(x,y)){
	    extern ClienteCapaBaja clienteCapaBaja;
	    clienteCapaBaja.Send((*it).first+" "+(*it).second.getVstr()+"\n\r");
	    cout << "envio" << endl;
	    break;
	}
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
