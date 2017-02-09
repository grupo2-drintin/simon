#ifndef SIMON_GAME_H
#define SIMON_GAME_H

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
 */


#ifndef STATUS_FLAGS
#define STATUS_FLAGS
#define S_ERROR     0
#define S_GAMEOVER  1
#endif //STATUS FLAGS: indican si el juego termino o no, o si hubo error


enum simon_colors {YELLOW, GREEN, BLUE, RED, LIGHTS_OFF};
//colores de las luces, e indicacion de que hay que apagarlas

#define IO_ALLEGRO  0
#define IO_RPI      1

#define IO          IO_ALLEGRO  //switch de compilacion: sistema de i/o


#define STANDARD_DELAY 250000
// tiempo que queda prendida cada luz durante el turno del jugador 

#define INITIAL_DELAY  1000000
#define DELAY_FRACTION 0.9
/* INITIAL_DELAY determinara cuanto tiempo quedara encendida la luz cuando co-
 * mience la secuencia, en microsegundos. antes de mostrar la secuencia otra vez,
 * este numero se ira multiplicando cada vez por DELAY_FRACTION, que debe ser
 * un numero mayor que 0 y menor que 1 para que la misma se muestre cada vez 
 * mas rapido. */





int simon_game (void);
/*  Ejecuta la totalidad del juego simon.
 *  Puede utilizar como sistema de input/output allegro o rpi (para cambiar se
 * debe modificar el define "IO" en el archivo backend_simon.h). En el caso de
 * allegro, se puede utilizar mouse o teclado como input, decidiendolo en cada
 * partida.
 *  El maximo puntaje alcanzado es almacenado en el archivo "highscores.txt",
 * que se genera automaticamente la primera vez que se ejecuta el programa en la
 * misma carpeta donde se este corriendo el mismo. 
 *  Se devolvera S_ERROR si hubo un error durante la ejecucion, y S_GAMEOVER si
 * el juego transcurrio normalmente. El usuario no puede ganar, si no que juega
 * hasta perder siempre. */



#endif /* SIMON_GAME_H */

