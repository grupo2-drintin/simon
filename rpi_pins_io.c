#include "rpi_pins_io.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CHAR_BUFFER 40 //tamano para arreglos de char

#define STR_GPIO    "/sys/class/gpio/gpio"
#define STR_EXP     "/sys/class/gpio/export"
#define STR_UNEXP   "/sys/class/gpio/unexport"
#define STR_VAL     "/value"
#define STR_DIR     "/direction"
#define STR_OUTPUT  "out"
#define STR_INPUT   "in"

#define HIGH '1'
#define LOW '0'

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif //TRUE


/* PREDECLARACIONES - FUNCIONES INTERNAS */
static int export (char * pin);
static int unexport (char * pin);
static int init_out (char * pin);
static int init_in(char * pin);
static int set_dir (char * pin, char * dir);



int set_pin(char * pin_number)
{
    FILE* handle_value;
    int error = TRUE;
    
    //obtiene el path del valor del pin
    char value_path[CHAR_BUFFER] = STR_GPIO;
    strcat(value_path, pin_number);
    strcat(value_path, STR_VAL);

    if ((handle_value = fopen(value_path,"w")) == NULL)
    {
        error = FALSE;   //marcar que hay error si no pudo abrir el pin
    }
    else 
    {    
        if (fputc (HIGH , handle_value) == -1) //escribe en el pin
        {
            error = FALSE; //marcar que hubo error si no pudo escribir en el pin
        }
        fclose(handle_value);
    }
    
    return error;
}




int clear_pin(char * pin_number)
{
    FILE* handle_value;
    int error = TRUE;
    
    //obtiene el path del valor del pin
    char value_path[CHAR_BUFFER] = STR_GPIO;
    strcat(value_path, pin_number);
    strcat(value_path, STR_VAL);
        
    if ((handle_value=fopen(value_path,"w")) == NULL)
    {
        error = FALSE;   //si no puede abrir el archivo: error
    }
    else
    {
        if (fputc (LOW, handle_value) == -1) //pone el pin en 0
        {
            error = FALSE;  //si no puede escribir en el archivo: error
        }
        fclose(handle_value);
    }
    
    return error;
}




int read_pin(char * pin_number)
{
    FILE* handle_value;
    int pin_value;
    
    //obtiene el path del valor del pin
    char value_path[CHAR_BUFFER] = STR_GPIO;
    strcat(value_path, pin_number);
    strcat(value_path, STR_VAL);

    if ((handle_value = fopen(value_path,"r")) == NULL)
    {
        pin_value = EOF;   //si no puede abrir el pin: error
    }
    else 
    {    
        if ( (pin_value = fgetc (handle_value)) != EOF);
        /* si hay error, se devolvera EOF. si no, se recibira 0 o 1 en ascii,
         * en cuyo caso hay que pasarlo a binario restandole '0' */
        {
            pin_value -= '0';
        }
        fclose(handle_value);            
    }
    
    return pin_value;
}



int init_gpios_in(char * pin_array[], int pin_number)
{
    int error=TRUE;

    while (pin_number>0 && error == TRUE)
    {
        pin_number--;                           //recorrer el arreglo de pines
        error&=init_in(pin_array[pin_number]); //inicializar
    }
    
    return error;
}




int init_gpios_out(char * pin_array[], int pin_number)
{
    int error=TRUE;
    
    while (pin_number>0 && error == TRUE)
    {
        pin_number--;                             //recorrer el arreglo de pines
        error&=init_out(pin_array[pin_number]);    //inicializar
    }
    
    return error;
}




int free_gpios(char * pin_array[], int pin_number)
{
    int error=TRUE;
      
    while (pin_number>0 && error==TRUE)
    {
        pin_number--;                           //recorrer el arreglo de pines
        error=unexport(pin_array[pin_number]);  //inexportar
    }

    return error;
}



static int set_dir(char * pin, char * dir)
{
    FILE* handle_direction;
    int n_written;
    int error=TRUE;
        
    /* Consigue el path de la direccion del pin: concatena el comienzo del
     * string, el numero de gpio y el final del string*/
    char dir_path[CHAR_BUFFER]= STR_GPIO;
    strcat(dir_path, pin);
    strcat(dir_path, STR_DIR);
    
    if ((handle_direction = fopen(dir_path, "w")) == NULL) //Abre el archivo
    {
        error=FALSE; //Control de error: se pudo abrir el archivo?
    }
    else
    {
        if ((n_written=fputs(dir, handle_direction)) == -1 ) //Setea como output
        {
            error=FALSE; //Control de error: se pudo escribir?
        }
        fclose(handle_direction);
    }
        
    return error;
}
    
    
    

static int init_out(char * pin)
{
    int error = TRUE;
        
    error=export(pin);                  //exporta el pin
    error&=set_dir(pin, STR_OUTPUT);    //lo configura como output
    /* el and logico hace que error solo sea TRUE si ambas funciones devolvieron
     * true, es decir si no hubo error en ninguna */
    
    return error;
}



static int init_in(char * pin)
{
    int error = TRUE;
        
    error=export(pin);                  //exporta el pin
    error&=set_dir(pin, STR_INPUT);     //lo configura como input
    /* el and logico hace que error solo sea TRUE si ambas funciones devolvieron
     * true, es decir si no hubo error en ninguna */
    
    return error;
}



static int unexport (char * pin)
{
    FILE* handle_unexport;
    int n_written;
    int error=TRUE;
    
    if ((handle_unexport = fopen(STR_UNEXP, "w")) == NULL) //abrir el archivo
    {
        error=FALSE;    //Control de error: se pudo abrir el archivo?
    }
    else
    {
        if ((n_written=fputs(pin, handle_unexport)) == -1 ) //liberar el pin
        {
            error=FALSE;    //Control de error: se pudo escribir?
        }
        fclose(handle_unexport);
    }
    
    return error;
}




static int export (char * pin)  
{
    FILE* handle_export;
    int n_written;
    int error=TRUE;
    
    if ((handle_export = fopen(STR_EXP, "w")) == NULL) //abrir el archivo
    {
        error=TRUE;    //Control de error: se pudo abrir el archivo?
    }
    else
    {
        if ((n_written=fputs(pin, handle_export)) == -1 ) //habilita el gpio
        {
            error=TRUE;    //Control de error: se pudo escribir?
        }
        fclose(handle_export);
    }
   
    return error;
}