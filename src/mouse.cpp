#include "mouse.h"
Mouse::Mouse()
{
    mouse_x=0;
    mouse_y=0;
}

void Mouse::BotonPresionado(int x,int y)
{
    mouse_x=x;
    mouse_y=y;
}

