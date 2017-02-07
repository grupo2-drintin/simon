/*
 * PROGRAMACION (22.07)
 * GRUPO 2: Rocio Parra, Paulo Daniel Navarro, Maria Luz Stewart Harris
 * TRABAJO PRACTICO N9
 * Fecha de entrega: lunes 24 de octubre de 2016
 *
 *   Las funciones contenidas en este modulo imprimen el contenido de 
 * una variable de 8 bits en codigo binario
*/

#ifndef RPI_PINS_IO_H
#define RPI_PINS_IO_H


#define HIGH '1'
#define LOW '0'


int set_pin(char * pin_number);

int clear_pin(char * pin_number);
/*
 * Funcion setpin / clearpin
 * Prende/ apaga un pin
 * Recibe el numero de pin que se quiere apagar (formato string)
 * Devuelve un bool. 1 si no hubo error, 0 si hubo error
 */



int read_pin(char * pin_number);
//lee el numero de pin que recibe como parametro (como string)
//devuelve el valor que leyo (1 o 0), o -1 si hubo un error

#endif /* RPI_PINS_IO_H */

