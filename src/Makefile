## Macros
DOC = ../dox
CC = g++
RM = rm -f
CFLAGS = -g -Wall -O2
SDL_CFLAGS := $(shell sdl-config --cflags)
SDL_LDFLAGS := $(shell sdl-config --libs)
EXTERN_LIBS = -L/usr/local/lib -ldxflib -lSDL_gfx -lsolarsockets++ -L/usr/X11R6/lib -lX11
PROGRAMA = gui
OBJ = selector.o gestorcamino.o gestorestado.o clientecapa_baja.o clientecapa_alta.o campo.o tabla.o punto.o linea.o polilinea.o capa.o mapa.o objetivo.o dxfparser.o dibujar.o frame.o etiqueta.o boton.o radar.o silla.o pantalla.o $(PROGRAMA).o

.SUFFIXES: .o .cpp

.cpp.o:
	$(CC) -c -o $@ $<

all: 	$(PROGRAMA)

$(PROGRAMA):	$(OBJ)
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(OBJ) -o $(PROGRAMA) $(EXTERN_LIBS)

clean:
	$(RM) $(OBJ) $(PROGRAMA)
	$(RM) -r $(DOC)/html $(DOC)/latex $(DOC)/dox-warnings.log $(DOC)/*.dvi $(DOC)/*.pdf $(DOC)/*.log $(DOC)/*.aux $(DOC)/*.d $(DOC)/*.toc

doc:
	@cd $(DOC)&& doxygen dox.conf; #>/dev/null;
	@echo "documentacion creada!"
#latex:
#	@cd $(DOC)&& pdflatex proyecto.tex && pdflatex proyecto.tex;
#	@echo "pdf creado!"
