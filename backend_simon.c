#include "char_buffer.h"
#include "backend_simon.h"

#include <stdint.h>
#include <time.h>

#if     IO == IO_ALLEGRO
#include "al_display_management.h"
#elif   IO == IO_RPI
#include "rpi_simon.h"
#else
#error
#endif  //IO





#define STANDARD_DELAY 250000
/* tiempo que queda prendida cada luz durante el turno del jugador */



#define CONTINUE    2 //indica que el jugador no perdio pero no termino el turno
 

static void display_w_sound(int);
/* Funcion interna: llama a las funciones que prenden/apagan la luz y el sonido
 * que se corresponde con la misma, sin devolver parametros y recibiendo el nu-
 * mero correspondiente al color (0-3) o la indicacion para que se apaguen todas
 * las luces (4).*/



void display_sequence(char_buffer_t sequence)
{
    static unsigned int delay = INITIAL_DELAY; 
    /* 'delay' es el tiempo en microsegundos entre que se prende y se apaga la
     * luz durante la secuencia de la maquina */
    
    int i;
    
    for (i=0; i<(sequence.n_written); i++)
    /* se muestran todos los elementos de la secuencia, que se encuentran a par-
     * tir de sequence.start y cuyo numero esta almacenado en n_written */    
    {
        display_w_sound(*(sequence.start + i));
        usleep(delay);
        display_w_sound(LIGHTS_OFF);
        usleep((int)(0.1*delay)); //para que se distinga cuando se repite un color
    }
    
    delay *= DELAY_FRACTION;   //la secuencia se muestra cada vez mas rapido
}



//la funcion user_attempt recibe != param. segun el i/o
#if IO == IO_ALLEGRO
int user_attempt(char_buffer_t correct_sequence, int event_source)
#else
int user_attempt(char_buffer_t correct_sequence)
#endif
{
    int status = CONTINUE;
    int i = 0;
    int last_event;
    
    while (status == CONTINUE)
    {
    /* el bloque while se ejecuta mientras que el usuario no se equivoque y no
     * se complete la secuencia, y verifica que se haya registrado un nuevo e-
     * vento. de ser asi, se compara el mismo con el que deberia haberse recibi-
     * do y se da el output apropiado */
        
        
//para allegro, get_event necesita saber si buscar eventos de teclado o mouse        
#if IO == IO_ALLEGRO
            last_event = get_event(event_source);
#else
            last_event = get_event();
#endif //IO        
            if (last_event == (*(correct_sequence.start + i)) )
            //compara lo que se recibio del jugador con la secuencia correcta
            {
                //si el usuario no se equivoca, se muestra lo que apreto     
                display_w_sound(*(correct_sequence.start + i));
                usleep(STANDARD_DELAY);
                display_w_sound(LIGHTS_OFF);
                
                if (++i == correct_sequence.n_written)
                //si se llego al final de la secuencia, termina el turno    
                {
                    status = SUCCESSFUL_ATTEMPT;
                }
            }
            else
            {
                status = WRONG_ATTEMPT; //el usuario perdio
            }
    }
    
    return status;
}


void correct_attempt(void)
{
    turn_light_on(TOP);       //prender todas las luces
    usleep((int)(STANDARD_DELAY*0.5));
    
    turn_light_on(RIGHT);
    usleep((int)(STANDARD_DELAY*0.5));
    
    turn_light_on(BOTTOM);
    usleep((int)(STANDARD_DELAY*0.5));
    
    turn_light_on(LEFT);
    usleep((int)(STANDARD_DELAY*0.5));
    
    turn_light_on(LIGHTS_OFF);    //apagar todas las luces
    usleep(STANDARD_DELAY * 2);
}




static void display_w_sound(int color)
{
    turn_light_on(color);   
    play_beep(color);
}