#include "fled.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_ERROR 1
#define ERROR 0

#define STR_GPIO  "/sys/class/gpio/gpio"
#define STR_DIR   "/direction"
#define STR_VAL   "/value"
#define STR_OUTPUT "out"
#define STR_INPUT   "in"

#define STR_EXP     "/sys/class/gpio/export"
#define STR_UNEXP    "/sys/class/gpio/unexport"

#define CHAR_BUFFER 40



static int export (char * pin);
static int unexport (char * pin);
static int init_out (char * pin);
static int init_in(char * pin);
static int set_dir (char * pin, char * dir);



int init_gpiosled(char * led_array[], int led_number)
{
    int error=NO_ERROR;
    /* el error es inicializado como 1 (indicacion de que no hubo error), y
     * luego inicializa cada pin que sea necesario. Si alguno de ellos devuelve
     * 0 (indicacion de error), al hacer un and logico con el mismo se seguira
     * mantiendo */
/*	system("cd ..");
	system("cd ..");
	system("cd ..");      */    
    while (led_number>0 && error == NO_ERROR)
    {
        led_number--;
        error&=init_out(led_array[led_number]);
    }
    return error;
}




int init_gpiosswi(char * switch_array[], int led_number)
{
    int error=NO_ERROR;
    /* el error es inicializado como 1 (indicacion de que no hubo error), y
     * luego inicializa cada pin que sea necesario. Si alguno de ellos devuelve
     * 0 (indicacion de error), al hacer un and logico con el mismo se seguira
     * mantiendo */
/*	system("cd ..");
	system("cd ..");
	system("cd ..");      */    
    while (led_number>0 && error == NO_ERROR)
    {
        led_number--;
        error&=init_in(switch_array[led_number]);
    }
    return error;
}




int free_gpios(char * led_array[], int led_number)
{
    int error=NO_ERROR;
     /* el error es inicializado como 1 (indicacion de que no hubo error), y
     * luego libera todos los pins. Si en algun momento se devuelve
     * 0 (indicacion de error), al hacer un and logico con el mismo se seguira
     * mantiendo */
    
    while (led_number>0 && error==NO_ERROR)
    {
        led_number--;
        error=unexport(led_array[led_number]);
    }
    /*
    error=unexport(PIN0);       //Liberacion de los pins
    error&=unexport(PIN1);
    error&=unexport(PIN2);
    error&=unexport(PIN3);
    error&=unexport(PIN4);
    error&=unexport(PIN5);
    error&=unexport(PIN6);
    */
    return error;
}



static int set_dir(char * pin, char * dir)
{
    FILE* handle_direction;
    int n_written;
    int error=NO_ERROR;
    
    
    /* Consigue el path de la direccion del pin: concatena el comienzo del
     * string, el numero de gpio y el final del string*/
    char dir_path[CHAR_BUFFER]= STR_GPIO;
    strcat(dir_path, pin);
    strcat(dir_path, STR_DIR);
    
    if ((handle_direction = fopen(dir_path, "w")) == NULL) //Abre el archivo
    {
        error=ERROR; //Control de error: se pudo abrir el archivo?
                       //si no, no intenta escribir en el mismo
    }
    else
    {
        if ((n_written=fputs(dir, handle_direction)) == -1 ) //Setea como output
        {
            error=ERROR; //Control de error: se pudo escribir?
        }
        fclose(handle_direction);
    }
    
 
    
    return error;
    
}
    
    
    

static int init_out(char * pin)
{
    int error = NO_ERROR;
        
    error=export(pin); //exporta el pin
    error&=set_dir(pin, STR_OUTPUT); //lo configura como output
    
    return error;
}



static int init_in(char * pin)
{
    int error = NO_ERROR;
        
    error=export(pin); //exporta el pin
    error&=set_dir(pin, STR_INPUT); //lo configura como input
    
    return error;
}



static int unexport (char * pin)
{
    FILE* handle_unexport;
    int n_written;
    int error=NO_ERROR;
    
    if ((handle_unexport = fopen(STR_UNEXP, "w")) == NULL) //abrir el archivo
    {
        error=ERROR;    //Control de error: se pudo abrir el archivo?
                       //si no, no intenta escribir en el mismo
    }
    else
    {
        if ((n_written=fputs(pin, handle_unexport)) == -1 ) //liberar el pin
        {
            error=ERROR;    //Control de error: se pudo escribir?
        }
         fclose(handle_unexport);
    }
    
    return error;
}




static int export (char * pin)  
{
    FILE* handle_export;
    int n_written;
    int error=NO_ERROR;
    
    if ((handle_export = fopen(STR_EXP, "w")) == NULL) //abrir el archivo
    {
        error=ERROR;    //Control de error: se pudo abrir el archivo?
                       //si no, no intenta escribir en el mismo
    }
    else
    {
        if ((n_written=fputs(pin, handle_export)) == -1 ) //habilita el gpio
        {
            error=ERROR;    //Control de error: se pudo escribir?
        }
        fclose(handle_export);
    
    }
   
    return error;
}
