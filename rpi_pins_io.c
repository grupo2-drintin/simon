#include "rpi_pins_io.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>


#define CHAR_BUFFER 40 //tamano para arreglos de char

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif TRUE

int set_pin(char * pin_number)
{
    FILE* handle_value;
    int error = TRUE;
    
    char value_path[CHAR_BUFFER] = "/sys/class/gpio/gpio";
    strcat(value_path, pin_number);
    strcat(value_path, "/value");

    if ((handle_value = fopen(value_path,"w")) == NULL)
    {
        error = FALSE;              //marcar que hay error
    }
    else 
    {    
        if (fputc (HIGH , handle_value) == -1)
        {
            error = FALSE;           //marcar que hubo error
        }
        fclose(handle_value);
    }
    return error;
}




int clear_pin(char * pin_number)
{
    FILE* handle_value;
    int error = TRUE;
    
    char value_path[CHAR_BUFFER] = "/sys/class/gpio/gpio";
    strcat(value_path, pin_number);
    strcat(value_path, "/value");
    
    
    if ((handle_value=fopen(value_path,"w")) == NULL)
    {
        error = FALSE;              //marcar que no hay error
    }
    else
    {
        if (fputc (LOW, handle_value) == -1)
        {
            error = FALSE;
        }
        fclose(handle_value);
    }
    return error;
}




int read_pin(char * pin_number)
{
    FILE* handle_value;
    int pin_value;
    
    char value_path[CHAR_BUFFER] = "/sys/class/gpio/gpio";
    strcat(value_path, pin_number);
    strcat(value_path, "/value");

    if ((handle_value = fopen(value_path,"r")) == NULL)
    {
        pin_value = -1;  //devuelve un valor que no es 0 ni 1 para marcar error
    }
    else 
    {    
        pin_value = fgetc (handle_value); //si no puede leer, devolvera
        fclose(handle_value);                       // EOF
    }
    
    return pin_value;
}