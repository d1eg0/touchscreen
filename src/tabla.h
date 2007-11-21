#ifndef TABLA_H
#define TABLA_H
#include <map>
#include <utility>
#include <string>
#include "campo.h"
#include "frame.h"
#include <iostream>
#include "clientecapa_baja.h"
using namespace std;

class Tabla{
public:
    Tabla();
    ~Tabla();

    void add(string n,Campo *c);
    Campo get(string n);
    void update(string n, string v, bool enviar);
    void update(string n, float v, bool enviar);
    void handle(int x, int y);
    void recargar(Frame *frame);

private:
    map<string, Campo> tabla;


};
#endif
