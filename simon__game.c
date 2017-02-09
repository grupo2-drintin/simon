#include "simon_game.h"

#include <stdlib.h>
#include <stdio.h>
#include "char_buffer.h"
#include "backend_simon.h"


#if     IO == IO_ALLEGRO            //define el medio de i/o: allegro o rpi
#include "al_display_management.h"
#elif   IO == IO_RPI
#include "rpi_simon.h"
#else
#error
#endif  //IO

#define S_CONTINUE  2      //flag de status

#define CB_INIT_SIZE    3  //Tamano inicial del buffer



int simon_game (void)
{
    static FILE * f_highscore;
    int highscore;
    int current_score = 0;
    int status = S_CONTINUE;

    char_buffer_t correct_sequence = create_cb(CB_INIT_SIZE);    
    /* en correct_sequence se almacenara la secuencia generada por la computa-
     * dora que el usuario debera emular. el uso del buffer circular no es 
     * estrictamente necesario (ya que no se borrara ningun elemento a lo largo
     * del juego), pero la funcion que escribe en el buffer lo agranda automati-
     * camente si se supera el espacio designado para el mismo y guarda simulta-
     * neamente un registro de cuantos elementos contiene, lo cual resulta util */
	if((f_highscore = fopen("highscores.txt", "r")) == NULL )
        //obtiene el highscore actual o crea un archivo para los highscore
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
            fscanf (f_highscore, "%d", &highscore); //recupera el highscore
            fclose (f_highscore);                   //hasta el momento
        }
    

#if IO == IO_RPI
    if (inicializacion()== EXIT_SIMON)
    {
        status = S_ERROR;
    }
    else
    {
        
        srand(time(NULL));
    
     
        while (status == S_CONTINUE)  
        //se ejecuta si no hubo errores y el jugador no perdio
        {
            write_cb(&correct_sequence, (char)(rand()%4));//agrega un color
            display_sequence(correct_sequence);//muestra toda la secuencia

            {   
                status = S_GAMEOVER; //si el jugador se equivoco termina el juego
                wrong_sequence();
            }    
            else
            {
                correct_attempt();
                
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
#else
 if (al_inicializacion(old_highscore)==EXIT_SIMON)
    {
        status = S_ERROR;
    }
    else
    {
        srand(clock()); //para poder obtener numeros random

        al_turn_light_on(LIGHTS_OFF);   //para que muestre el display
        al_kb_or_mouse();               //elige el modo de input
     
        while (status == S_CONTINUE)  
        //se ejecuta si no hubo errores y el jugador no perdio
        {
            write_cb(&correct_sequence, (char)(rand()%4));//agrega un color
            display_sequence(correct_sequence);//muestra toda la secuencia

            if (user_attempt(correct_sequence) == SUCCESSFUL_ATTEMPT)
            //user attempt: turno del jugador
            {         
                al_correct_attempt(); //indicar al jugador que gano un punto
                
                if (++current_score > old_highscore)
                //actualizar el highscore si hace falta
                {
                    updated_highscore = current_score;
                }
                al_update_score(current_score);
            }    
            else
            {
                status = S_GAMEOVER; //si el jugador se equivoco termina simon
                al_wrong_attempt();    //indicarle al usuario que perdio
                
                if (updated_highscore != 0)
                //esta condicion solo se cumple si hay un nuevo highscore 
                {
                    al_new_highscore(updated_highscore);
                    if((f_highscore = fopen("highscores.txt", "w")) == NULL )
                    {
                        status = S_ERROR;
                    } 
                    else
                    {
                        //guardar el nuevo highscore
                        fprintf(f_highscore, "%d", updated_highscore);
                        fclose(f_highscore);
                    }
                }
                
                al_finalizacion();
                //allegro:solo se finaliza si no hubo error en init
            }    
        }
    }   
    

#endif
    free_cb(&correct_sequence);
    
    return status;      //status va a indicar si hubo error o no
}

