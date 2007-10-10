#include "boton.h"
#include "constantes.h"
#include <string>
#include <SDL/SDL_gfxPrimitives.h>

using namespace std;

Boton::Boton(SDL_Surface *Ventana)
{
	area.h=20;
	area.w=40;
	area.x=0;
	area.y=0;
	texto="?";
	ventana=Ventana;
	Sizef=16;
	//fuente= TTF_OpenFont("georgia.ttf",Sizef);
	Stylef=0;
	//TTF_SetFontStyle (Font, TTF_STYLE_NORMAL);

	//HiHaSombra=true;
	estado=inactivo;

}

Boton::~Boton()
{

}

bool Boton::getEstado(){
    return estado;
}
/*
void Boton::CanviaMidaText(int mida)
{
	Font= TTF_OpenFont("georgia.ttf",mida);
	TTF_SetFontStyle (Font, TTF_STYLE_NORMAL);
}

void Boton::EscribirTexto()
{
	SDL_Color Blanc = {255,255,255,0}; 	
	SDL_Rect AreaAux;
	AreaAux = Destf;
	

	if(EstatBoto==seleccionat)
	{	SurfaceF = TTF_RenderText_Blended(Font,text,Blanc);
		AreaAux.x=Destf.x + 3;
		AreaAux.y=Destf.y + 3;
	}
	else
		SurfaceF = TTF_RenderText_Blended(Font,text,fontColor);
	if(SDL_BlitSurface(SurfaceF, NULL, Finestra, &AreaAux)==-1)
			printf("Falla Blit Surface\n");

	SDL_UpdateRect(Finestra,AreaAux.x,AreaAux.y,AreaAux.w,AreaAux.h);

	SDL_FreeSurface(SurfaceF);
}

void Boto::LlevarSombra(bool Som)
{
	HiHaSombra=Som;
}

*/
void Boton::cargarBoton(int x, int y, int w, int h, char *c, Uint32 color)
{
	this->color=color;
	area.h=h;
	area.w=w;
	area.x=x;
	area.y=y;
	//TTF_SizeText(Font,_texto,&wt,&ht);

	contenedor.x=area.x;
	contenedor.y=area.y;
	contenedor.w=w;
	contenedor.h=h;
	
	SDL_SetClipRect(ventana, &area);
	boxColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, color);
	rectangleColor(ventana, area.x, area.y, area.x+area.w-1, area.y+area.h-1, 0xffffffff);
	string str(c);
	stringColor(ventana,
		(int)( area.x+(area.w*0.5)-(SIZE_C*str.size()*0.5)), 
		(int)(area.y+(area.h*0.5)-(SIZE_C*0.5)), 
		c, 
		0xffffffFF);
	SDL_UpdateRect(ventana, 0, 0, SCREEN_W, SCREEN_H);
	estado=activo;
}

/*void Boton::dibujarBoton()
{
	SDL_Rect sombra;
	Uint32 ColorAux;
	ColorAux=color;

	sombra.x=area.x + 3;
	sombra.y=area.y + 3;
	sombra.h=area.h; 
	sombra.w=area.w;

	if(estado==deseleccionado)
	{
		if(HiHaSombra)
		{
			SDL_FillRect(Finestra, &Sombra,SDL_MapRGB(Finestra->format,0,0,0));
			SDL_UpdateRect(Finestra,Sombra.x,Sombra.y,Sombra.w,Sombra.h);
		} 
		//SDL_SetAlpha(ventana, SDL_SRCALPHA, 255);
		//SDL_FillRect(ventana, &area, color);
		boxColor(ventana,area.x,area.y,area.x+area.w,area.y+area.h,color);
		SDL_UpdateRect(ventana,area.x,area.y,area.w,area.h);
	}
	else
	{
	    if(Color+(3*50)<255*255*255)
			ColorAux=Color+(3*50);
		else
			if(Color<255*255*255)
				ColorAux=255*255*255;

		
		SDL_Rect EspaiBlanc;
		EspaiBlanc.x=Area.x;
		EspaiBlanc.y=Area.y;
		EspaiBlanc.w=Area.w+3;
		EspaiBlanc.h=Area.h+3;

		SDL_FillRect(Finestra, &EspaiBlanc,SDL_MapRGB(Finestra->format,200,200,200));
		SDL_UpdateRect(Finestra,EspaiBlanc.x,EspaiBlanc.y,EspaiBlanc.w,EspaiBlanc.h);

		SDL_FillRect(Finestra, &Sombra, ColorAux);
		SDL_UpdateRect(Finestra,Sombra.x,Sombra.y,Sombra.w,Sombra.h);
		
	}

	
  //  EscriureText();
}*/

/*
void Boto::InsereixText(char *_text)
{
	text=_text;
}

bool Boto::EsDedins(int xm, int ym)
{
	if (xm >= Area.x && xm <= Area.x+Area.w && ym >= Area.y && ym <= Area.y+Area.h)
	{
		return true;
	}
	return false;
}

void Boto::CanviarEstat()
{
	if (EstatBoto== seleccionat)
		EstatBoto= deseleccionat;
	else
		EstatBoto= seleccionat;
}

void Boto::Seleccionar()
{
	EstatBoto=seleccionat;
	DibuixaBoto();
}
void Boto::Deseleccionar()
{
	EstatBoto=deseleccionat;
	DibuixaBoto();
}

bool Boto::EstaDeseleccionat()
{
	if(EstatBoto==deseleccionat)
		return true;
	else
		return false;
}

bool Boto::EstaSeleccionat()
{
	if(EstatBoto==seleccionat)
		return true;
	else
		return false;
}

int Boto::GetX()
{
	return Area.x;
}
int Boto::GetY()
{
	return Area.y;
}
int Boto::GetH()
{
	return Area.h;
}
int Boto::GetW()
{
	return Area.w;
}
*/
bool Boton::presionado(int x,int y)
{
	return estado&&(x>area.x)&&(x<area.x+area.w)&&
		(y>area.y)&&(y<area.y+area.h);
}

