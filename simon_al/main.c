#include <stdio.h>
#include <stdlib.h>
#include "al_display_management.h"

void main (void) 
{
    inicializacion();
    int key;
    while(key != EXIT_SIMON)
    {
        key = get_event();
        turn_light_on(key);
    }
    finalizacion();
    return 0;
}

