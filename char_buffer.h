#ifndef CHAR_BUFFER_H
#define CHAR_BUFFER_H

/* 
 *  PROGRAMACION I
 *
 *  GRUPO 2
 *
 *  TRABAJO PRACTICO N 12 - EJERCICIO 1
 *
 *  CONSIGNA: Se debe implementar una librería para generar buffers circulares
 * de caracteres. El mismo debe permitir:
 * - Crear múltiples buffers;
 * - Ingresar un nuevo dato al final,
 * - sacar el primer dato de la cola,
 * - indicar si el buffer se encuentra lleno.
 *
 *  FECHA DE ENTREGA: lunes 14 de noviembre de 2016
 *
 */


#include <stdint.h>

#ifndef TRUE        //Valores de TRUE y FALSE, con los que se indica el error
#define TRUE    1
#endif  //TRUE

#ifndef FALSE
#define FALSE   0
#endif //FALSE

typedef struct cb 
{
    char * start;       //Direccion inicial del buffer
    uint32_t size;      //Numero de elementos que se puede contener en el mismo
    uint32_t write;     //Fin de la cola
    uint32_t read;      //Comienzo de la cola
    uint32_t n_written; //Numero de elementos presentes en la cola    
}char_buffer_t; //Tipo de dato char_buffer_t: buffer circular de caracteres

char_buffer_t create_cb (uint32_t n_elements);
/* Recibe el numero de chars que va a tener el buffer
 * Crea el buffer y lo devuelve, listo para usar. */

void free_cb (char_buffer_t *cb);
/* Recibe la direccion del buffer, libera la memoria usada para el mismo.
 * Para prevenir que se intente utilizar el buffer una vez liberado el mismo,
 * se reemplaza su direccion inicial por un puntero a null. */

int write_cb (char_buffer_t * cb, char last_in);
/* Recibe la direccion del buffer y el char que se desea escribir en el mismo
 * De no encontrarse lleno el buffer, guarda el caracter recibido al final de 
 * la cola y devuelve TRUE.
 * De lo contrario, devuelve FALSE */


char read_cb (char_buffer_t * cb, int* error);
/* Recibe la direccion del buffer del cual se desea leer, y la direccion de un
 * int por el cual se indicara si hubo error.
 * Si no se desease hacer control de errores, se puede enviar un puntero a NULL
 * Si hay aun cosas por leer en el buffer, devuelve lo primero en la cola y 
 * TRUE en el indicador de error.
 * De lo contrario, indica error con FALSE (el valor devuelto no tendra ningun
 * significado).*/


int is_full_cb (char_buffer_t cb);
/* Verifica el estado del buffer recibido. 
 * De encontrarse lleno, devuelve TRUE, y de lo contrario, FALSE.*/

void cb_clear (char_buffer_t * cb);
/* Vacia el buffer, ignorando todo lo que se ha escrito y aun no se ha leido
 * hasta ese momento. Entonces, lo que se lea luego sera lo que se recibio des-
 * pues de invocar a esta funcion */

/* 
 * Ejemplo de uso de las funciones de esta libreria:
 
#include <stdio.h>
#include "char_buffer.h"

int main (void)
{
    int error;
    char first_in;
    char string[]="Hola mundo 12341234"; //"Hola mundo" son 10 caracteres
 
    int i=0;
 
    char_buffer_t cb = create_cb(10); //Crea un buffer circular de 10 elementos
 
    while (!is_full_cb(cb))
    // Esta condicion se verificara cuando se hayan escrito 10 caracteres.
    // Es equivalente a hacer "while (error) { error = write_cb... }
    {
        write_cb(&cb, string[i]);   //Escribe del string al buffer
        i++;
    }
    
    while (error)
    // Se saldra del loop cuando se hayan leido todos los caracteres.
    // Es equivalente a hacer "while (cb.n_written)" e ignorar el error
    {
        putchar(read_cb(&cb, &error));
    }    
    putchar('\n');
    
    free_cb(&cb);   //Libera la memoria asignada al buffer
} 
 */


#endif //CHAR_BUFFER_H