#include "campotexto.h"
#include "constantes.h"
#include <string>
#include <SDL/SDL_gfxPrimitives.h>

using namespace std;

Campotexto::Campotexto(Frame *frame, 
	string nombre, 
	float valor, 
	float vmax, 
	float vmin, 
	float incremento)
{
    this->frame=frame;
    this->nombre=nombre;
    this->valor=valor;
    this->maxvalor=vmax;
    this->minvalor=vmin;
    this->incremento=incremento;
    bmas=new Boton(frame->getVentana());
    bmenos=new Boton(frame->getVentana());
}

Campotexto::~Campotexto()
{

}


void Campotexto::cargarCampotexto(int x, int y, Uint32 colorNombre, Uint32 colorValor)
{
    this->colorNombre=colorNombre;
    this->colorValor=colorValor;
    this->arean.x=x;
    this->arean.y=y;
    this->arean.w=SIZE_C*nombre.size();
    this->arean.h=SIZE_C*2;
    
		
    SDL_SetClipRect(frame->getVentana(),  &arean);

    stringColor(
	    frame->getVentana(),
	   (int)( arean.x+(arean.w*0.5)-(SIZE_C*nombre.size()*0.5)), 
	    (int)(arean.y+(arean.h*0.5)-(SIZE_C*0.5)), 
	    nombre.c_str(), 
	    colorNombre);
    
    char *valorc=(char *)malloc(sizeof(float));
    sprintf(valorc,"%5.3f",this->valor);
    this->areav.x=x+arean.w;
    this->areav.y=y;
    this->areav.w=SIZE_C*string(valorc).size();
    this->areav.h=SIZE_C*2;
    SDL_SetClipRect(frame->getVentana(),  &areav);
    stringColor(
	    frame->getVentana(),
	    areav.x, 
	    (int)(areav.y+(areav.h*0.5)-(SIZE_C*0.5)), 
	    valorc, 
	    colorValor);
    
    bmas->cargarBoton(	    
	    areav.x+areav.w+20, 
	    y, 
	    20,
	    20,
	    "+",
	    0x01F33EFF);
    bmenos->cargarBoton(	    
	    areav.x+areav.w+40, 
	    y, 
	    20,
	    20,
	    "-",
	    0xFF4848FF);
	//SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
}

