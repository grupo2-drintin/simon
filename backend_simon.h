#ifndef BACKEND_SIMON_H
#define BACKEND_SIMON_H

/* 
 *  PROGRAMACION I
 *
 *  GRUPO 2 - 2do cuatrimestre de 2016:
 *  -Navarro, Paulo
 *  -Parra, Rocío
 *  -Stewart Harris, María Luz
 *
 *  TRABAJO PRACTICO FINAL - SIMON
 *
 *  CONSIGNA: Se deberá diseñar e implementar el juego Simon, para que pueda 
 * visualizarse de manera gráfica en una computadora, captando el teclado y el 
 * mouse, y en una RaspberryPi con el set de botones y LEDs provisto por la cá-
 * tedra. Para cambiar entre una versión y otra, se deberá utilizar un switch de
 * compilación.
 *
 *  FECHA DE ENTREGA: Viernes 10 de febrero de 2017
 *
 * 
 * Back-end del juego Simon: funciones del turno de la maquina y del jugador.
 * 
 * 
 */




#define IO_ALLEGRO  0
#define IO_RPI      1

#define IO          IO_ALLEGRO

#define WRONG_ATTEMPT       0   //indicacion de si el usuario se equivoco o no
#define SUCCESSFUL_ATTEMPT  1

#define INITIAL_DELAY  1000000
#define DELAY_FRACTION 0.9
/* INITIAL_DELAY determinara cuanto tiempo quedara encendida la luz cuando co-
 * mience la secuencia, en microsegundos. antes de mostrar la secuencia otra vez,
 * este numero se ira multiplicando cada vez por DELAY_FRACTION, que debe ser
 * un numero mayor que 0 y menor que 1 para que la misma se muestre cada vez 
 * mas rapido. */


void display_sequence(char_buffer_t sequence);
/* Muestra la secuencia de colores contenida en el buffer. Cada vez que se llama
 * a la funcion, la misma se mostrara mas rapidamente, de acuerdo a INITIAL_DELAY
 * y DELAY_FRACTION */



#if IO == IO_ALLEGRO
int user_attempt(char_buffer_t correct_sequence, int event_source);

#else
int user_attempt(char_buffer_t);

#endif //IO
/*  user_attempt: turno del jugador en el juego simon.
 *  Recibe un buffer circular con la secuencia correcta hasta ese punto, y en el
 * caso de que se este utilizando allegro tambien una indicacion de si se usa 
 * mouse o teclado, que se obtene por la funcion kb_or_mouse contenida en 
 * al_display_management.c.
 *  Cada vez que el jugador elige el color que cree que sigue en la secuencia, 
 * lo compara con la misma. Si es correcto, prende la luz y emite el sonido que
 * le corresponde y avanza al siguiente elemento hasta el ultimo. Si adivina to-
 * da la secuencia correctamente, devuelve SUCCESSFUL_ATTEMPT. De lo contrario,
 * devuelve WRONG_ATTEMPT. */



void correct_attempt(void);
/* Prende todas las luces y espera una fraccion de segundo, de forma tal que sea
 * claro cuando termina el turno del jugador y empieza la secuencia de la
 * maquina  */






#endif //BACKEND_SIMON_H