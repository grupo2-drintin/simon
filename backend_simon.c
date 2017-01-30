#include "backend_simon.h"
#include "char_buffer.h" 
#include <stdint.h>
#include <time.h>

#define MICROSECONDS 1000000 //pasar de segundos a microsegundos
#define STANDARD_DELAY  2,5 //en segundos
#define OFF 0


#define ERROR       0
#define CONTINUE    2
#define SUCCESS     1

#define NO_EVENT    0


extern void display_w_sound(char);
extern void start_input(void);
extern int get_next_event(void);
extern void stop_input(void);

void display_sequence(char_buffer_t sequence, int delay)
{
    int i;
    
    for (i=0; i<(sequence.n_written); i++)
    {
        display_w_sound(*(sequence.start + i));
        usleep(delay*MICROSECONDS);
        display_w_sound(OFF);
    }
}


int user_attempt(char_buffer_t correct_sequence)
{
    int status = CONTINUE;
    int i = 0;
    int last_event;
    
    start_input();
    
    while (status == CONTINUE)
    {
        if((last_event = get_next_event) != NO_EVENT)
        {
            if (last_event == (*(correct_sequence.start + i)) )
            {
                display_w_sound(*(correct_sequence.start + i));
                usleep(STANDARD_DELAY*MICROSECONDS);
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
    }
    
    stop_input();
    
    return status;
}




