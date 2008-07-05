#include "tabla.h"
#include "constantes.h"
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
}

void Tabla::update(string n, float v){
    stringstream buffer;
    buffer << v;

    tabla.find(n)->second.updateValor(v);
}

void Tabla::handle(int x,int y){
    map<string, Campo>::iterator it;
    for (it=tabla.begin();it!=tabla.end();it++){
	if((*it).second.handle(x,y)){
	    extern ClienteCapaAlta clienteCapaAlta;
	    clienteCapaAlta.Send((*it).first+(*it).second.getVstr()+"\r\n");
	    cout << "envio:" << (*it).first+(*it).second.getVstr()+"\r\n" <<  endl;
	    break;
	}
    }
}

void Tabla::recargar(Frame *frame){
    int x=frame->getX();
    int y=frame->getY();
    map<string, Campo>::iterator it;
    bool columna=false;;
    for (it=tabla.begin();it!=tabla.end();it++){
	(*it).second.recargar(x+5,y+5);
	y+=20;
	if(y>(frame->getY()+frame->getH()-20)){
	    if(frame->getEstado()==MAXIMO){
		if(!columna){
		    x+=300;
		    y=frame->getY();
		    columna=true;
		}
	    }else{
		break;
	    }
	}
    }
}
