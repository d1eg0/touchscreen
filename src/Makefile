## Macros

CC = g++
RM = rm -f
CFLAGS = -g -Wall -O2
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs)
EXTERN_LIBS = -L/usr/local/lib -ldxf -lSDL_gfx -lSDL_ttf -lsolarsockets++ -L/usr/X11R6/lib -lX11
PROGRAMA = gui
OBJ = gestorcamino.o gestorestado.o clientecapa_baja.o clientecapa_alta.o campo.o punto.o linea.o polilinea.o capa.o mapa.o objetivo.o dxfparser.o dibujar.o frame.o etiqueta.o boton.o radar.o pantalla.o $(PROGRAMA).o

.SUFFIXES: .o .cpp

.cpp.o:
	$(CC) -c -o $@ $<

all: 	$(PROGRAMA)

$(PROGRAMA):	$(OBJ)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(OBJ) -o $(PROGRAMA) $(EXTERN_LIBS)

clean:
	$(RM) $(OBJ) $(PROGRAMA)
