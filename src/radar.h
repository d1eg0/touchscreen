#include "punto.h"
#include "frame.h"
#include <vector>
#include <SDL/SDL_thread.h>
using namespace std;

/**
 *  \class Radar
 *  \brief El radar indica los obst&aacute;culos pr&oacute;ximos y la orientaci&oacute;n de la silla.
 *   
 *  \par 
 */

class Radar{
public:
    /** Instancia del radar */
    Radar(Frame *frame);
    ~Radar();
    /** Recarga el radar, 'refresh' a true si se precisa refrescar */
    void recargar(bool refresh);
    /** Devuelve la componente X del radar */
    int getX();
    /** Devuelve la componente Y del radar */
    int getY();
    /** Devuelve el radio de la circunferencia m&aacute;s peque&ntilde;a */
    int getR1();
    /** Devuelve el radio de la circunferencia mediana */
    int getR2();
    /** Devuelve el radio de la circunferencia m&aacute;s grande */
    int getR3();
    /** Devuelve el frame que contiene el radar */
    Frame *getFrame();
    /** Devuelve la lista de obst&aacute;culos */
    vector<Punto> getObstaculos();
    /** A&ntilde;adir un nuevo punto 'o' */
    void addObstaculo(Punto o);
    /** Dibuja la flecha que indica la rotaci&oacute;n de la silla */
    void dibujarFlecha(int rot);
    /** Devuelve el Surface donde se pinta la flecha */
    SDL_Surface *getFlecha();
    /** Devuelve el desplazamiento */
    SDL_Rect getDesp();
private:
    SDL_Thread *s;
    vector<Punto> lobstaculos;
    Frame* frame;
    int xm,
	ym;
    Uint32 color;
    int r[3];
    SDL_Rect desp;
    int rot;
    SDL_Surface *flecha;
};
