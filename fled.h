/*
 * PROGRAMACION I
 * GRUPO 2: Navarro, Paulo Daniel
 *          Parra, Rocio
 *          Stewart Harris, Maria Luz
 * 
 * TP 9(c): Estructuras, uniones y drivers
 * 
 * Este modulo permite inicializar y liberar los gpio de la Raspberry Pi
 */

#ifndef FLED_H
#define FLED_H



int init_gpiosled(char * led_array[], int led_number);
/* Funcion de inicializacion de los gpios
   Recibe el arreglo que contiene los strings con los numeros de gpios que se utilizaran
para los leds, asi como el numero de leds.
   Exporta dichos gpios y los configura como output
   Devuelve un 1 si no hubo error y un 0 en el caso contrario  */

int init_gpiosswi(char * switch_array[], int led_number);



int free_gpios(char * led_array[], int led_number);
/* Esta funcion debe invocarse una vez que se hayan terminado de usar los pines previamente 
habilitados. Recibe los mismos parametros que init_gpios y devuelve el mismo codigo de error */


#endif /* FLED_H */

