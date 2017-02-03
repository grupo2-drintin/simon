#include <stdio.h>
#include <stdlib.h>
#include "al_display_management.h"

void main (void) 

//NOTA: ESTE MAIN DE VERGA ES SOLO PARA CHEQUEAR QUE TODO FUNCIONE.
//POR AHORA, JUEVES A LA NOCHE, LO QUE NO AnDA ES LA FINALIZACION
{
    inicializacion();
    
    
    int key = LIGHTS_OFF;
    turn_light_on(key);
    int source_of_events = kb_or_mouse();
    while(key != EXIT_SIMON)
    {
        key = get_event( source_of_events );
        turn_light_on(key);
        play_beep(key);
    }
    finalizacion();
}

