#include "simon_game.h"

#include <stdlib.h>
#include <stdio.h>
#include "char_buffer.h"

#if     IO == IO_ALLEGRO            //define el medio de i/o: allegro o rpi
#include "al_display_management.h"
#elif   IO == IO_RPI
#include "rpi_simon.h"
#else
#error
#endif  //IO

#define S_CONTINUE  2       //flag de status interna

#define CB_INIT_SIZE    20
//Tamano inicial del buffer donde se almacena la secuencia

#define WRONG_ATTEMPT       0   //indicacion de si el usuario se equivoco o no
#define SUCCESSFUL_ATTEMPT  1




static void display_sequence(char_buffer_t sequence);
/* Muestra la secuencia de colores contenida en el buffer. Cada vez que se llama
 * a la funcion, la misma se mostrara mas rapidamente, de acuerdo a INITIAL_DELAY
 * y DELAY_FRACTION */


static int user_attempt(char_buffer_t);
/*  user_attempt: turno del jugador en el juego simon.
 *  Recibe un buffer circular con la secuencia correcta hasta ese punto.
 *  Cada vez que el jugador elige el color que cree que sigue en la secuencia, 
 * lo compara con la misma. Si es correcto, prende la luz y emite el sonido que
 * le corresponde y avanza al siguiente elemento hasta el ultimo. Si adivina to-
 * da la secuencia correctamente, devuelve SUCCESSFUL_ATTEMPT. De lo contrario,
 * devuelve WRONG_ATTEMPT. */

static void display_w_sound(int);
/*   Llama a las funciones que prenden/apagan la luz y el sonido que se corres-
 * ponde con la misma, sin devolver parametros y recibiendo el numero que indica
 * el color (0-3) o la indicacion para que se apaguen todas las luces (4).*/


int simon_game (void)
{
    static FILE * f_highscore;
    
    int old_highscore;
    int updated_highscore = 0;  //si no se alcanza un nuevo highscore, quedara en 0
    
    int current_score = 0;
    int status = S_CONTINUE;

    char_buffer_t correct_sequence = create_cb(CB_INIT_SIZE);    
    /* en correct_sequence se almacenara la secuencia generada por la computa-
     * dora que el usuario debera emular. el uso del buffer circular no es 
     * estrictamente necesario (ya que no se borrara ningun elemento a lo largo
     * del juego), pero la funcion que escribe en el buffer lo agranda automati-
     * camente si se supera el espacio designado para el mismo y guarda simulta-
     * neamente un registro de cuantos elementos contiene */

   
    if((f_highscore = fopen("highscores.txt", "r")) == NULL )
    /* obtiene el highscore actual o crea un archivo para los highscore.
     * se guardara el highscore hasta el momento en old_highscore (si no existia,
     * sera 0) */
    {
        if((f_highscore = fopen("highscores.txt", "w")) == NULL )
        //si no existia el archivo, lo crea
        {
            status = S_ERROR; //si tampoco puede crearlo: error
        }    
        else
        {
            fputc(0, f_highscore);  //si no habia highscore, empieza en 0
        }
    }
    if (status != S_ERROR) //si pudo abrir el archivo:
    {
        fscanf (f_highscore, "%d", &old_highscore); //recupera el highscore
        fclose (f_highscore);                       //hasta el momento
    }
    
    
    
#if IO == IO_ALLEGRO    //inicializacion() tiene != param. segun el i/o
    if (al_inicializacion(old_highscore)==EXIT_SIMON)
    {
        status = S_ERROR;
    }
    else
    {
        srand(clock()); //para poder obtener numeros random

        al_turn_light_on(LIGHTS_OFF);   //para que muestre el display
        int event_source = al_kb_or_mouse(); //elige el modo de input
     
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
    
#else

    if (rpi_inicializacion()==EXIT_SIMON) //distinto de al: no recibe param.
    {
        status = S_ERROR;
    }
    else
    {
        srand(time(NULL)); //para poder obtener numeros random

        while (status == S_CONTINUE)  
        //se ejecuta si no hubo errores y el jugador no perdio
        {
            write_cb(&correct_sequence, (char)(rand()%4));//agrega un color
            display_sequence(correct_sequence);//muestra toda la secuencia

            if (user_attempt(correct_sequence) == SUCCESSFUL_ATTEMPT)
            //user attempt: turno del jugador
            {   
                rpi_correct_attempt(); //indicar al jugador que gano un punto
                
                if (++current_score > old_highscore)
                //actualizar el highscore si hace falta
                {
                    updated_highscore = current_score;
                }
            }    
            else
            {
                
                status = S_GAMEOVER; //si el jugador se equivoco termina simon
                rpi_wrong_attempt();    //indicarle al usuario que perdio
                
                if (updated_highscore != 0)
                //esta condicion solo se cumple si hay un nuevo highscore 
                {
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
            }    
        }
    }
       
    rpi_finalizacion();     //hay que finalizar aunque haya habido un error     
    
#endif    
    free_cb(&correct_sequence);
    
    return status;      //status va a indicar si hubo error o no
}



static void display_sequence(char_buffer_t sequence)
{
    static unsigned int delay = INITIAL_DELAY; 
    /* 'delay' es el tiempo en microsegundos entre que se prende y se apaga la
     * luz durante la secuencia de la maquina */
    
    int i;
    
    for (i=0; i<(sequence.n_written); i++)
    /* se muestran todos los elementos de la secuencia, que se encuentran a par-
     * tir de sequence.start y cuyo numero esta almacenado en n_written */    
    {
        display_w_sound(*(sequence.start + i)); //prender la luz y el sonido
        usleep(delay);
        
        display_w_sound(LIGHTS_OFF);            //apagarlos
        usleep((int)(0.1*delay));
        //pequeno delay para que se distinga cuando se repite un color
    }
    
    delay *= DELAY_FRACTION;   //la proxima vez se mostrara mas rapido
}



static int user_attempt(char_buffer_t correct_sequence)
{
    int status = S_CONTINUE;
    int i = 0;
    int last_event;
    
    while (status == S_CONTINUE)
    {
    /* el bloque while se ejecuta mientras que el usuario no se equivoque y no
     * se complete la secuencia, y verifica que se haya registrado un nuevo e-
     * vento. de ser asi, se compara el mismo con el que deberia haberse recibi-
     * do y se da el output apropiado */
    
#if IO == IO_ALEGRO
        last_event = al_get_event();   //recibe que color toco el jugador
#else 
        last_event = rpi_get_event();
#endif // get event
        
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



static void display_w_sound(int color)
{
#if IO == IO_ALLEGRO    
    al_turn_light_on(color);   //prender la luz
    al_play_beep(color);       //prender el audio
#else
    rpi_turn_light_on(color);
    rpi_play_beep(color);
#endif //turn light on, play beep    
/* en el caso de recibir LIGHTS_OFF, al llamar a estas dos funciones se apagan
 * la luz y el sonido */ 
}
