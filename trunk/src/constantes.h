/**
 *       @file  constantes.h
 *
 *     @author  Diego García , kobydiego@gmail.com
 *
 *   @internal
 *     Company  Universitat de les Illes Balears
 *   Copyright  Copyright (c) 2009, Diego García
 *
 *
 *  This file is part of TouchScreenGUI.
 *  TouchScreenGUI is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  TouchScreenGUI is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TouchScreenGUI; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  http://www.gnu.org/copyleft/gpl.html
 *
 * =====================================================================================
 */

//Color de fondo
#define	    COLOR_BG	0x000000
#define	    COLOR_BORDER_BOTON	0xFFFFFFFF
#define	    COLOR_FUENTE	0x0066FFFF
#define	    COLOR_BORDER_FRAME	0x0066FFFF
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
#define	    FACTOR_DESP	10

//Zoom máximo y mínimo
#define	    ZOOM_MAX	1500
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
#define	    CABECERA_MAPA	"[MAPA] "
#define	    CABECERA_INIRUTA    "[RUTA] "
#define	    CABECERA_FINRUTA    "[FIRU] "
#define	    CABECERA_ERROR	"[ERRO] "
#define	    CABECERA_STATUS	"[STAT] "
#define	    CABECERA_OBJETIVO	"[OBJE] "
#define	    CABECERA_SENS    	"[SENS] "
#define	    CABECERA_POS    	"[POSI] "
#define	    CABECERA_GRID    	"[GRID] "
#define	    CABECERA_DOBST    	"[DOBS] "
#define	    CABECERA_FLAGS    	"[FLAG] "
