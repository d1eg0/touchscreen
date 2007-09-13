## Macros

CC = g++
RM = rm
CFLAGS = -g -Wall -O2
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs)
OBJ = boton.o pantalla.o main.o

all: $(OBJ)
	$(CC) -g $(CFLAGS) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(OBJ) -o main 

clean:
	$(RM) $(OBJ) main

# Reglas implícitas
main.o: 
	$(CC) -c main.cpp -g
pantalla.o: pantalla.cpp pantalla.h
	$(CC) -c pantalla.cpp -g
boton.o: boton.cpp boton.h
	$(CC) -c boton.cpp -g
