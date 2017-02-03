#include "simon_game.h"

#include <stdlib.h>
#include <stdio.h>
#include "char_buffer.h"
#include "backend_simon.h"


#if     IO == IO_ALLEGRO
#include "al_display_management.h"
#elif   IO == IO_RPI
#include "rpi_simon.h"
#else
#error
#endif  //IO



#define CB_INIT_SIZE    100  //Tamano inicial del buffer



int simon_game (void)
{
    static FILE * f_highscore;
    int highscore;
    int current_score = 0;
    int status = S_CONTINUE;

    char_buffer_t correct_sequence = create_cb(CB_INIT_SIZE);    


    if (inicializacion()==-1)
    {
        status = S_ERROR;
    }
    else
    {
        if((f_highscore = fopen("highscores.txt", "r")) == NULL )
        //este bloque if obtiene el highscore actual o crea un archivo para los highscore
        {
            if((f_highscore = fopen("highscores.txt", "w")) == NULL )
            {
                status = S_ERROR;
            }
            else
            {
                fputc(0, f_highscore);  //si no habia highscore, empieza en 0
                fclose(f_highscore);
            }
        } 
        else
        {
            fscanf (f_highscore, "%d", &highscore);
            fclose (f_highscore);
        }
    
        srand(clock());

#if IO == IO_ALLEGRO
        int event_source = kb_or_mouse();
#endif  //IO           
     
        while (status == S_CONTINUE)  
        //se ejecuta si no hubo errores y el jugador no perdio
        {
            write_cb(&correct_sequence, (char)(rand()%4));//agrega un color
            display_sequence(correct_sequence);//muestra toda la secuencia

#if IO == IO_ALLEGRO
            if (user_attempt(correct_sequence, event_source) == WRONG_ATTEMPT)
#else                       
            if (user_attempt(correct_sequence) == WRONG_ATTEMPT)
#endif //IO: dependiendo de si se usa allegro o rpi user_attempt tiene != param.
            {   
                status = S_GAMEOVER; //el jugador se equivoco
            }    
            else
            {
                if (++current_score > highscore)
                //actualizar el highscore si hace falta, en la var. y el arch.
                {
                    highscore = current_score;
                
                    if((f_highscore = fopen("highscores.txt", "w")) == NULL )
                    {
                        status = S_ERROR;
                    } 
                    else
                    {
                        fprintf(f_highscore, "%d", highscore);
                        fclose(f_highscore);
                    }
                }
            }    
        }
    }
       
    finalizacion();     //hay que finalizar aunque haya habido un error 
    free_cb(&correct_sequence);
    
    return status;      //status va a indicar si hubo error o no
}

