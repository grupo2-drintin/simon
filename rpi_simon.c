#include "rpi_simon.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "rpi_pins_io.h"
#include "simon_game.h"
#include "char_buffer.h"
#include "libaudio.h"


#define LED_RED     "4"     //Numero de pin correspondiente a cada led y switch
#define SWI_RED     "17"    
#define LED_GREEN   "18"
#define SWI_YELLOW  "22"
#define SWI_GREEN   "23"
#define LED_BLUE    "24"
#define SWI_BLUE    "25"
#define LED_YELLOW  "27"

#ifndef TRUE
#define TRUE    1
#define FALSE   0
#endif

#define SWI_ON  0
#define SWI_OFF 1

#define NO_EVENT       LIGHTS_OFF + 1 //codigo que no corresponde a ningun evento

#define GAMEOVER_SOUND LIGHTS_OFF + 1 //codigo que corresponde al sonido "buzz"

#define BUFFER_INIT_SIZE 100 //tamano inicial del buffer de eventos


static void * input_thread(); //Predeclaracion: thread de lectura
static void play_color(char * AudioFile); //predeclaracion

static int keep_reading;
static char_buffer_t buffer;

static char AudioFile_RED[]="./Sound/red.wav";
static char AudioFile_GREEN[]="./Sound/green.wav";
static char AudioFile_BLUE[]="./Sound/blue.wav";
static char AudioFile_YELLOW[]="./Sound/yellow.wav";
static char AudioFile_BUZZ[]="./Sound/buzz.wav";

static const char * led_array[] =       //numero de gpio que
{LED_YELLOW, LED_RED, LED_GREEN, LED_BLUE}; //corresponde a cada led    
static const char * switch_array[] =       //numero de gpio que
{SWI_YELLOW, SWI_RED, SWI_GREEN, SWI_BLUE}; //corresponde a cada led




int rpi_inicializacion(void)
{ 
    int error = TRUE;

    if(!init_gpios_out(led_array, sizeof(led_array)/sizeof(char *)))
    //inicializar los leds
    {
        printf("Error. Cannot initialize pins(LED's). Try again later\n");
        error = EXIT_SIMON;
    }    
    
    if(!init_gpios_in(switch_array, sizeof(switch_array)/sizeof(char *)))
    //inicializar los switches    
    {
        printf("Error. Cannot initialize pins(switchs). Try again later\n");
        error = EXIT_SIMON;
    }
    
    init_sound(); // Init sound driver
        
    return error;
}




void rpi_finalizacion(void)
{ 
    if(!free_gpios(led_array, sizeof(sizeof(led_array)/sizeof(char *))))
    //liberar los leds
    {
        printf("Warning: could not unexport pins (led's)\n");
    }
    
    if(!free_gpios(switch_array, sizeof(sizeof(switch_array)/sizeof(char *))))
    //liberar los switches    
    {
        printf("Warning: could not unexport pins (switchs)\n");
    }
    
}



void rpi_turn_light_on (int color)
{
    switch (color)
    {
        /* Colores (YELLOW, RED, GREEN, BLUE):
     `   * Encender la luz correspondiente */   
        case BLUE:
        {
            set_pin(LED_BLUE);
        }
        break;
        case RED:
        {
            set_pin(LED_RED);
        }
        break;
        case YELLOW:
        {
            set_pin(LED_YELLOW);
        }
        break;
        case GREEN:
        {
            set_pin(LED_GREEN);
        }
        break;   
        
        case LIGHTS_OFF:    //apagar todas las luces
        {
            clear_pin(LED_RED);
            clear_pin(LED_GREEN);
            clear_pin(LED_BLUE);
            clear_pin(LED_YELLOW);
        }    
    
    }
}



int rpi_get_event(void)
{
    int event = NO_EVENT;
    
    while (event == NO_EVENT)       //espera a que haya un nuevo evento
    {
        if (buffer.n_written != 0)  //verifica si ya hay algun evento
        {
            event = read_cb(&buffer, NULL); //si hay un evento, lo devuelve
        }    
    }
    
    return event;
}



void rpi_start_input(void)
{
    buffer=create_cb(BUFFER_INIT_SIZE);  //Buffer donde se guardaran los eventos
        
    pthread_t r_kb;
    pthread_create(&r_kb, NULL, input_thread, NULL);  //Comienza a leer el input
}




void rpi_stop_input(void)
{
    keep_reading = FALSE;   //Detiene el thread de lectura
    free_cb(&buffer);       //Libera la memoria utilizada por el buffer
}




static void * input_thread()
/* Thread de lectura de teclado */
{
    keep_reading = TRUE;    //valor inicial para que se ejecute el thread
    
    while (keep_reading = TRUE)        //repite hasta que se llame a stop
    {
        /* lee el valor de todos los pines, y si alguno esta apretado agrega el
         * evento correspondiente a la cola y luego hace un pequeno delay, para
         * que no se interprete como que se apreto varias veces un boton solo
         * porque se mantuvo apretado una fraccion de segundo */
        
        if (read_pin(SWI_GREEN) == SWI_ON)
        {
            write_cb(&buffer, GREEN);
            usleep(300000);
        }
        
        if (read_pin(SWI_BLUE) == SWI_ON)
        {
            write_cb(&buffer, BLUE);
            usleep(300000);
        }
        
        if (read_pin(SWI_RED) == SWI_ON)
        {
            write_cb(&buffer, RED);
            usleep(300000);
        }
        
        if (read_pin(SWI_YELLOW) == SWI_ON)
        {
            write_cb(&buffer, YELLOW);
            usleep(300000);
        }
    }
}




void rpi_correct_attempt(void)
{

    set_pin(LED_BLUE);       //prender todas las luces, una por una
    usleep((int)(STANDARD_DELAY*0.5));
    
    turn_light_on(GREEN);
    usleep((int)(STANDARD_DELAY*0.5));
    
    set_pin(LED_RED);
    usleep((int)(STANDARD_DELAY*0.5));
    
    set_pin(LED_YELLOW);
    usleep((int)(STANDARD_DELAY*0.5));
    
    
    turn_light_on(LIGHTS_OFF);    //apagar todas las luces
    usleep(STANDARD_DELAY * 2);
}




void rpi_wrong_attempt(void)
{
    play_beep(GAMEOVER_SOUND); //ruido de derrota
    set_pin(LED_BLUE);         //prender todas las luces
    set_pin(LED_RED);
    set_pin(LED_YELLOW);
    set_pin(LED_GREEN);
    
    sleep(1);                   //mantener 1 segundo
    
    end_play();                 //apagar todo
    turn_light_on(LIGHTS_OFF);
}



void rpi_play_beep(int color)
{
    switch (color)
    {
    /* Colores (YELLOW, RED, GREEN, BLUE):
     * Hacer sonar el audio correspondiente */    
        case YELLOW: 
	{	
            play_color(AudioFile_YELLOW); 	
	}
        break;
        case RED:
	{	
            play_color(AudioFile_RED);
        }
        break;
	case GREEN:
        {	
            play_color(AudioFile_GREEN); 		 
   	}
        break;
	case BLUE:		
        {	
            play_color(AudioFile_BLUE); 		
   	}
        break;
	        
	case LIGHTS_OFF:    //apagar lo que sea que este sonando
        {	
            end_play(); 				  
   	}
        break;
        
        case GAMEOVER_SOUND: //efecto especial para cuando el jugador pierde
        {       
            play_color(AudioFile_BUZZ);
        }
        break;
    }
}




static void play_color(char * AudioFile) // Non blocking Audio File
/* FUNCION PROPORCIONADA POR LA CATEDRA
 * Quitamos el printf que indicaba que sonido estaba reproduciendose */
{
	
	if(player_status()==READY)
	{
			
	//	printf(GREEN_TEXT "Playing: %s \n",AudioFile); 	printf(WHITE_TEXT);
	
		set_file_to_play(AudioFile);      // Load file 			
	
		play_sound(); 			 // Play File (Non Blocking)
                

		return;
	}
	else
	{
			
            printf(RED_TEXT "System not ready did you run init_sound() ? \n" WHITE_TEXT );
				
            exit(-1);		
	}
	
}