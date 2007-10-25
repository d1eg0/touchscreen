//Constantes

//Resolución de la pantalla
#define	    SCREEN_W    640 //anchura
#define	    SCREEN_H    480 //altura
//#define	    SCREEN_W    1280 //anchura
//#define	    SCREEN_H    800 //altura


#define	    BORDER	2
#define	    MARGEN	20

//Estado Frame
#define	    CERRADO	0 //frame cerrado
#define	    MAXIMO	1 //frame con tamaño maximo
#define	    MINIMO	2 //frame con tamaño mínimo

//Tamaño caracter (alto y ancho)
#define	    SIZE_C	8

//Factor de aumento y reducción del zoom
#define	    FACTOR_ZOOM	25

//Factor de desplazamiento del mapa
#define	    FACTOR_DESP	25

//Zoom máximo y mínimo
#define	    ZOOM_MAX	300
#define	    ZOOM_MIN	25

//Tamaño boton
#define	    T_BOTON	20

//Zonas frame
//	    Ventana
//  ____________________________
//  |				|
//  |		1		|
//  |....... ________...........|
//  |	    |	    |		|
//  |	    |	5   |		|
//  |	2   |	    |	  4	|
//  |	    |_______|		|			    
//  |	    :	3   :		|
//  |_______:_______:___________|
//
//
#define	    Z_ARRIBA	0x1
#define	    Z_IZQUIERDA 0x2
#define	    Z_ABAJO	0x4
#define	    Z_DERECHA	0x8
#define	    Z_CENTRO	0x10


//Identificadores de los clientes
#define	    CLIENTEPLANO    0
#define	    CLIENTELOG	    1
#define	    CLIENTESENS	    2
