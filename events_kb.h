#ifndef EVENTS_KB_H
#define EVENTS_KB_H

/* 
 *  PROGRAMACION I
 *
 *  GRUPO 2
 *
 *  TRABAJO PRACTICO N 12 - EJERCICIO 2
 *
 *  CONSIGNA: Se deberá realizar una librería que capture eventos de teclado y 
 * los ponga en una cola para que puedan ser utilizados por cualquier programa. 
 * La misma debe correr de manera paralela, para que pueda estar capturando e-
 * ventos constantemente sin interrumpir la ejecución del programa principal.
 *
 *  FECHA DE ENTREGA: lunes 14 de noviembre de 2016
 *
 */

#include "nonblock.h"      
#include "char_buffer.h"
#include <pthread.h>
#include <stdio.h>


void start_read_kb(void);
/* Comienza a guardar el input del teclado.
 * Debe tenerse en cuenta que se comenzara a usar el modo no canonico de lectura
 * de teclado, y es necesario que se mantenga el mismo hasta que se llame a 
 * stop_read_kb */


void stop_read_kb(void);
/* Deja de guardar el input del teclado.
 * Debe tenerse en cuenta que si quedasen eventos sin procesar, no podra acce-
 * derse a los mismos una vez llamada esta funcion */


char get_next_event(void);
/* Devuelve el proximo caracter en la cola. De no haber nuevos eventos, devuelve
 * FALSE (0)*/


#endif /* EVENTS_KB_H */