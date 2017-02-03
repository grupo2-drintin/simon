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


#define ONE_SECOND  1000000 //un millon de microsegundos = un segundo

#define STANDARD_DELAY 250000 //tres cuartos de segundo
#define OFF 4


#define ERROR       0
#define CONTINUE    2
#define SUCCESS     1

#define NO_EVENT    0


static void display_w_sound(int);



void display_sequence(char_buffer_t sequence)
{
    static unsigned int delay = ONE_SECOND; //usleep recibe microsegundos
    
    int i;
    
    for (i=0; i<(sequence.n_written); i++)
    {
        display_w_sound(*(sequence.start + i));
        usleep(delay);
        display_w_sound(OFF);
    }
    
    delay *= 0.9;   //la secuencia se muestra cada vez mas rapido
}

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
        
#if IO == IO_ALLEGRO
            last_event = get_event(event_source);
#else
            last_event = get_event();
#endif //IO        
            if (last_event == (*(correct_sequence.start + i)) )
            {
                display_w_sound(*(correct_sequence.start + i));
                usleep(STANDARD_DELAY);
                display_w_sound(OFF);
                
                if (++i == correct_sequence.n_written)
                {
                    status = SUCCESS;
                }
            }
            else
            {
                status = ERROR;
            }
    }
    
    return status;
}




static void display_w_sound(int color)
{
    turn_light_on(color);
    play_beep(color);
}