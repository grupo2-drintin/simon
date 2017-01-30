#include "events_kb.h"


#ifndef TRUE
#define TRUE    1
#endif  //TRUE

#ifndef FALSE
#define FALSE   0
#endif  //TRUE

#define CB_INIT_SIZE 200    //Tamano inicial del buffer


static void * read_kb_thread(); //Predeclaracion

static int keep_reading=TRUE;     
static char_buffer_t buffer;


void start_read_kb(void)
{
    nonblock(NB_ENABLE);            //Desabilita el modo canonico de ingreso
    
    buffer=create_cb(CB_INIT_SIZE);  //Buffer donde se guardaran los eventos
    
    pthread_t r_kb;
    pthread_create(&r_kb, NULL, read_kb_thread, NULL);  //Comienza a leer el kb
}



static void * read_kb_thread()
/* Thread de lectura de teclado */
{
    char last_in;
    
    while (keep_reading) //repite hasta que el buffer este lleno o se llame a stop
    {
        if(kbhit())
        {
            last_in=getchar();      //De haberse apretado una tecla, la obtiene
            
            if(!is_full_cb(buffer))
            {
                write_cb(&buffer, last_in); //Guarda el ultimo evento, si no 
            }                               //esta lleno el buffer
            else
            {
                keep_reading=FALSE;         
            }
        }
    }
}

char get_next_event(void)
{
    int could_read; 
    
    char next_event = read_cb(&buffer, &could_read);  //Obtiene el ultimo evento
    
    if (!could_read)
    {
        next_event=FALSE;                      //Si se indico error, devuelve 0 
    }
    
    return next_event;
}



void stop_kb_read(void)
{
    keep_reading=FALSE;     //Detiene el thread de lectura de teclado
    nonblock(NB_DISABLE);   //Vuelve al modo canonico
    free_cb(&buffer);       //Libera la memoria utilizada por el buffer
}