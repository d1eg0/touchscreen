//Color de fondo
#define	    COLOR_BG	0x000000
#define	    COLOR_BORDER_BOTON	0xFFFFFFFF
//Constantes dimensiones
#define	    SCREEN_W	640
#define	    SCREEN_H	480

#define	    BORDER	2
#define	    MARGENH	20
#define	    MARGENV	30

//Estado Frame
#define	    CERRADO	0 //frame cerrado
#define	    MAXIMO	1 //frame con tamaño maximo
#define	    MINIMO	2 //frame con tamaño mínimo

//Tamaño caracter (alto y ancho)
#define	    SIZE_C	8

//Factor de aumento y reducción del zoom
#define	    FACTOR_ZOOM	50

//Factor de desplazamiento del mapa
#define	    FACTOR_DESP	20

//Zoom máximo y mínimo
#define	    ZOOM_MAX	900
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
#define	    Z_TOTAL	0x1F	

//Identificadores de los clientes
#define	    TRAMAPLANO	    0
#define	    TRAMAOBJETIVO   1
#define	    CLIENTESENS	    2

//Respuesta al pulsar objetivo
#define	    SIN_RESPUESTA   0
#define	    RESPUESTA_SI    1
#define	    RESPUESTA_NO    2

//Colores
#define	    COLORCAMINO	    0xff0000ff

//Cabeceras protocolo
#define	    CABECERA_MAPA	"[MAPA]"
#define	    CABECERA_ERROR	"[ERROR]"
#define	    CABECERA_INIRUTA    "[RUTA]"
#define	    CABECERA_FINRUTA    "[FIN_RUTA]"
#define	    CABECERA_STATUS	"[STATUS]"
#define	    CABECERA_POS    	"[PRA]"
#define	    CABECERA_SENS    	"[SENS]"

