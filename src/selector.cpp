#include "selector.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <iostream>
#include "frame.h"
#include "constantes.h"
#include "mapa.h"
#include "pantalla.h"
Selector::Selector(SDL_Surface* pantalla){
    this->ventana=pantalla;
}

Selector::~Selector(){
    mapas.clear();
}

//Gestiona la muerte del hijo
void reaper(int iSignal)
{
    int estado;
    pid_t pid;
    pid=wait3((int *)&estado,WNOHANG,0);

    extern Selector *selector;
    if(estado==0){
	selector->buscarR();
	selector->cargar();
    }
    signal(SIGCHLD,reaper); //reset handler to catch SIGCHLD for next time;
}


void Selector::buscarR(){
    char *buffer=(char*)malloc(1024);
    read(descf[0],buffer,1024);
    string bufstr(buffer);
    size_t pos=bufstr.find('\n');
    while(pos!=string::npos){
	mapas.push_back(bufstr.substr(0,pos));
	bufstr.erase(0,pos+1);					
	pos=bufstr.find('\n');
    }
    vector<string>::iterator it;
    for(it=mapas.begin();it!=mapas.end();it++){
	cout << (*it) <<  endl;
    }
    free(buffer);
}

void Selector::buscarW(string ruta,string ext){
    this->ruta=ruta;
    this->ext=ext;
    string exp="*."+ext;
    signal(SIGCHLD,reaper);
    if(pipe(descf)<0) printf("pipe");
    switch (fork()) {
	case -1:
            cerr << "Error: fork";
        case 0:
	    close(2);
	    close(1);
	    if(dup(descf[1])<0) printf("Error: dup");
	    execlp("find","find",ruta.c_str(),"-name",exp.c_str(),(char*)0);
            cerr << "Error: exec";
    }
}

void Selector::cargar(){
    extern Frame* frameselector;
    frameselector=new Frame(ventana);
    frameselector->cargarFrame(
	    MARGENH,
	    MARGENV,
	    (int)((float)SCREEN_W/10.0*6.0), 
	    (int)((float)SCREEN_H/10.0*7.5),
	    "Mapas",0xffffff);


    int dx=frameselector->getX()+5;
    int y=frameselector->getY();
    int dy=y+5;
    int dv=30;
    int dh=frameselector->getW()-10;
    vector<string>::iterator it;
    for(it=mapas.begin();it!=mapas.end();it++){
	Boton b(ventana);
	b.cargarBoton(dx,dy,dh,dv,(char*)(*it).c_str(),0xff9999ff);
	lista.push_back(b);
	dy+=dv;
    }
    //se bloquea el mando de control del mapa
    extern Pantalla *pantalla;
    pantalla->mapaOff();
}

bool Selector::handle(int x,int y){
    vector<Boton>::iterator boton;
    extern Mapa plano;
    extern Pantalla *pantalla;
    for(boton=lista.begin();boton!=lista.end();boton++){
	if((*boton).presionado(x,y)){
	    cout << "presionado: " << (*boton).getTexto()<< endl;
	    plano.lectura((*boton).getTexto()); 
	    pantalla->minimizar();
	    return true;
	}
    }
    return false;
}
bool Selector::vacio(){
    cout << mapas.size() << endl;
    return mapas.empty();
}

