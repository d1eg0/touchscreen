#include "punto.h"
#include "frame.h"
#include <vector>
#include <SDL/SDL_thread.h>
using namespace std;
class Radar{
public:
    Radar(Frame *frame);
    ~Radar();
    void recargar(bool refresh);
    //void escan();
    int getX();
    int getY();
    int getR1();
    int getR2();
    int getR3();
    Frame *getFrame();
private:
    SDL_Thread *s;
    vector<Punto> lobstaculos;
    Frame* frame;
    int xm,
	ym;
    Uint32 color;
    int r1,
	r2,
	r3;
};
