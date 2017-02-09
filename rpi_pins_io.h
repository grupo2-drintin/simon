#ifndef RPI_PINS_IO_H
#define RPI_PINS_IO_H

/*
 * PROGRAMACION (22.07)
 * GRUPO 2: Rocio Parra, Paulo Daniel Navarro, Maria Luz Stewart Harris
 * (2do cuat. 2016)
 *  
 *  Este modulo permite exportar, inexportar y configurar la direccion de pines
 * de una Rasperry Pi, asi como leer el estado y escribir en ellos 
*/


int init_gpios_out(char * pin_array[], int pin_number);
int init_gpios_in(char * pin_array[], int pin_number);
/* FuncionEs de inicializacion de los gpios en modo output o input:
 * Reciben el arreglo que contiene los strings con los numeros de gpios que se 
 * utilizaran, asi como el numero de pins contenidos en el mismo.
 * Exporta dichos gpios y los configura como output o input segun corresponda
 * Devuelve un 1 si no hubo error y un 0 en el caso contrario  */


int free_gpios(char * pin_array[], int pin_number);
/* Esta funcion debe invocarse una vez que se hayan terminado de usar los pines
 * previamente habilitados. Recibe los mismos parametros que init_gpios y devuel-
 * ve el mismo codigo de error */


int set_pin(char * pin_number);
int clear_pin(char * pin_number);
/* Funciones set/clear pin
 * Prende/ apaga un pin
 * Recibe el numero de pin que se quiere prender/apagar (formato string)
 * Devuelve un bool: 1 si no hubo error, 0 si hubo error
 */


int read_pin(char * pin_number);
//lee el numero de pin que recibe como parametro (como string)
//devuelve el valor que leyo (1 o 0), o -1 si hubo un error

#endif /* RPI_PINS_IO_H */

