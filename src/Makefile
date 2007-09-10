## Macros

CC = g++
RM = rm
CFLAGS = -g -Wall -O2
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs)
SRC = main.cpp
OBJ = main.o

all: $(OBJ)
	$(CC) -g $(CFLAGS) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(OBJ) -o main 

clean:
	$(RM) $(OBJ) main

# Reglas implícitas
main.o: 
	$(CC) -c main.cpp -g
