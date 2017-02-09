#ifndef RPI_SIMON_H
#define RPI_SIMON_H

#define EXIT_SIMON -1 //indicacion de error en la inicializacion

int inicializacion(void);
/* Inicializacion: inicializa los leds, los switches y el sistema de audio.
 * Devuelve TRUE (1) si no hubo error, y EXIT_SIMON (-1) si lo hubo.
 * Debe llamarse antes de tratar de prender/apagar algun led, tratar de leer
 * el input recibido por los switches o hacer sonar alguna pista de audio. */

void finalizacion (void);
/* Finalizacion: libera los pines utilizados.
 * Debe llamarse antes de cerrar el programa si previamente se llamo a 
 * inicializacion(). */

void start_input(void);
/* Comienza a fijarse si se aprieta algun switch. Debe llamarse antes de utili-
 * zar get_event(). */

int get_event(void);
/* Devuelve el color correspondiente al boton que se apreto. Bloquea el programa
 * hasta que se apriete alguno. */

void stop_input(void);
/* Descarta los eventos que no se leyeron hasta el momento, y deja de verificar
 * el estado de los switches hasta que se vuelva a llamar a start_input */

void turn_light_on (int);
/* Segun el int que reciba, prende la luz del color indicado (0-3) o apaga todas
 * las luces (4) */

void play_beep(int);
/* Segun el int que reciba, hace que suene la pista correspondiente al color in-
 * dicado (0-3), silencia lo que sea que este sonando (4), o hace sonar el ruido
 * "buzz" (5). Una vez que se le pasa una pista para hacer sonar, no se debe 
 * volver a menos que sea para hacerla apagarse, y luego si puede elegirse otra
 * pista. */

void correct_attempt(void);
/* efecto de que el jugador gano un punto: prende una por una las luces y luego
 * las apaga todas al mismo tiempo, con un pequeno delay luego */

void wrong_attempt(void);
/* efecto de que el jugador perdio: emite el sonido "buzz" y prende todas las 
 * luces durante un segundo */

#endif /* RPI_SIMON_H */
