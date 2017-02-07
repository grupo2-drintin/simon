#include "rpi_simon.h"

#include "rpi_pins_io.h"
#include "backend_simon.h"
#include "char_buffer.h"
#include "fled.h"
#include <pthread.h>



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

#define SWI_ON  48
#define SWI_OFF 49

#define NO_EVENT 5      //codigo que no corresponde a ningun evento

#define BUFFER_INIT_SIZE 100



static void * input_thread(); //Predeclaracion: thread de lectura

static int keep_reading;     
static char_buffer_t buffer;

const char * led_array[] =       //numero de gpio que
{LED_YELLOW, LED_RED, LED_GREEN, LED_BLUE}; //corresponde a cada led    
const char * switch_array[] =       //numero de gpio que
{SWI_YELLOW, SWI_RED, SWI_GREEN, SWI_BLUE}; //corresponde a cada led


int inicializacion(void)
{ 
    int error = TRUE;
   /* system("cd ..");
    system("cd ..");
    system("cd .."); */
        if(!init_gpiosled(led_array, sizeof(led_array)/sizeof(char *)))
        {
            printf("Error. Cannot initialize pins(LED's). Try again later\n");
            error = EXIT_SIMON;
            
        }    
    
        if(!init_gpiosswi(switch_array, sizeof(switch_array)/sizeof(char *)))
        {
            printf("Error. Cannot initialize pins(switchs). Try again later\n");
            error = EXIT_SIMON;
        }
    return error;
}

void finalizacion(void)
{ 
    if(!free_gpios(led_array, sizeof(sizeof(led_array)/sizeof(char *))))
	{
            printf("Warning: could not unexport pins (led's)\n");
	}
    
    if(!free_gpios(switch_array, sizeof(sizeof(switch_array)/sizeof(char *))))
	{
            printf("Warning: could not unexport pins (switchs)\n");
	}
    
}



void turn_light_on (int color)
{
    switch (color)
    {
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
        
        case LIGHTS_OFF:
        {
            clear_pin(LED_RED);
            clear_pin(LED_GREEN);
            clear_pin(LED_BLUE);
            clear_pin(LED_YELLOW);
        }    
    
    }
}



int get_event(void)
{
    int event = NO_EVENT;
    
    while (event == NO_EVENT)
    {
        if (buffer.n_written != 0)
        {
            event = read_cb(&buffer, NULL);
        }    
    }
    
    return event;
}



void start_input(void)
{
    buffer=create_cb(BUFFER_INIT_SIZE);  //Buffer donde se guardaran los eventos
    
    keep_reading = TRUE;
    
    pthread_t r_kb;
    pthread_create(&r_kb, NULL, input_thread, NULL);  //Comienza a leer el input
}


void stop_input(void)
{
    keep_reading = FALSE;   //Detiene el thread de lectura
    free_cb(&buffer);       //Libera la memoria utilizada por el buffer
}





static void * input_thread()
/* Thread de lectura de teclado */
{
    while (keep_reading) //repite hasta que el buffer este lleno o se llame a stop
    {
        if (read_pin(SWI_GREEN) == SWI_ON)
        {
            write_cb(&buffer, GREEN);
            usleep(500000);
        }
        
        if (read_pin(SWI_BLUE) == SWI_ON)
        {
            write_cb(&buffer, BLUE);
            usleep(500000);
        }
        
        if (read_pin(SWI_RED) == SWI_ON)
        {
            write_cb(&buffer, RED);
            usleep(500000);

        }
        
        if (read_pin(SWI_YELLOW) == SWI_ON)
        {
            write_cb(&buffer, YELLOW);
            usleep(500000);

        }
    }
}

