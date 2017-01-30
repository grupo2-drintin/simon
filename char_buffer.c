#include "char_buffer.h"
#include <stdlib.h>

#define CB_MAX_SIZE  1000   //Maximo tamano al que se puede expandir el buffer
#define CB_STEP      100    //De a cuanto se incrementa el buffer cuando se su-
                            //pera su capacidad actual

#define CB_REALLOCATE 2     //indicacion de que se necesita agrandar el buffer





char_buffer_t create_cb (uint32_t n_elements)
{
    char_buffer_t new_buffer={.size=n_elements, .n_written=0, .read=0, .write=0};
    /* Inicializa el nuevo buffer con el tamano recibido, e indica que se encuen-
     * tra vacio actualmente. Read y write se deben inicializar obligatoriamente
     * en la misma posicion, aunque es indistinto en cual. */
    
    new_buffer.start = calloc(sizeof(char), n_elements);
    //Reserva memoria para el buffer
    
    return new_buffer;   
}


void free_cb (char_buffer_t *old_buffer)
{
    free(old_buffer->start);    //Libera la memoria utilizada
    old_buffer->start=NULL;     //Borra el valor anterior del puntero
}

int write_cb (char_buffer_t * cb, char last_in)
{
    int error;
    
    switch (is_full_cb(*cb))
    {
        case (CB_REALLOCATE):    //Se ejecuta este caso y el siguiente
        {
            cb->size+=CB_STEP;  //Antes de escribir, agranda el buffer
            cb->start = realloc(cb->start, cb->size);
        }
        
        case (TRUE):
        {
            cb->start[cb->write]= last_in;  //Escribe en el final de la cola
            cb->n_written++;                //Indica que se escribio un char mas
        
            if (cb->write==cb->size)
            {  
                cb->write=0;    //Si se llego al final del buffer, vuelve al co-
            }                   //mienzo
            else
            {  
                cb->write++;    //De lo contrario, avanza a la sig posicion
            }
         
            error = TRUE;         //Indica que no hubo error        
        }
        break;
        
        case (FALSE):
        {
            error = FALSE;
        }
        break;
    }
    
    

/*

    if (!is_full_cb(*cb))   //Verifica que quede lugar para escribir
    {
        cb->start[cb->write]= last_in;  //Escribe en el final de la cola
        cb->n_written++;                //Indica que se escribio un char mas
        
        if (cb->write==cb->size)
        {  
            cb->write=0;    //Si se llego al final del buffer, vuelve al comienzo
        }
        else
        {
            cb->write++;    //De lo contrario, avanza a la sig posicion
        }
         
        error=TRUE;         //Indica que no hubo error
    }
    else
    {
        error=FALSE;    //Si la condicion inicial es falsa: error
    }
*/    
    return error;
}



char read_cb (char_buffer_t * cb, int* error)
{
    char first_in_line;

    if (cb->n_written)  //Verifica que haya algo nuevo para leer
    {
        first_in_line = cb->start[cb->read]; //Lee desde el principio de la cola
        cb->n_written--;               //Indica que queda un char menos por leer
        
        if (cb->read == cb->size)
        {
            cb->read = 0;  //Si se llego al final del buffer, vuelve al comienzo
        }
        else
        {
            cb->read++;   //De lo contrario, avanza a la siguiente posicion
        }
    
        if(error)       //Verifica que no se haya recibido puntero a null
        {
            *error=TRUE;    //Indica que no hubo error
        }      
    }    
    else
    {
        if(error)       //Verifica que no se haya recibido puntero a null
        {
            *error=FALSE;   //Si no se cumple la condicion inicial: error
        }
    }
    
    return first_in_line;
}


int is_full_cb (char_buffer_t cb)
{
    int isfull=TRUE;
    
    /* Condicion para que el buffer este lleno: el numero de caracteres que se ha
     * escrito es igual al tamano del buffer completo
     * Si esta lleno, chequea si se puede agrandar*/
    if (cb.n_written != cb.size)
    {
        if (cb.size + CB_STEP <= CB_MAX_SIZE)
        {
            isfull = CB_REALLOCATE;
        }
        else
        {
            isfull = FALSE;   
        }
    }
    
    return isfull;
}


void cb_clear (char_buffer_t * cb)
{
    cb->n_written = 0;      //Indica que no hay nada nuevo para leer
    cb->write = cb->read;   //Iguala los offsets de read y write para que el bu-
                            //ffer continue funcionando con normalidad
}