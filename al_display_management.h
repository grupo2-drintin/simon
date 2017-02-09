#ifndef AL_DISPLAY_MANAGEMENT_H
#define AL_DISPLAY_MANAGEMENT_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_font.h" 
#include "allegro5/allegro_ttf.h" 
#include "allegro5/allegro_native_dialog.h"
#include "al_img_prop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define EXIT_SIMON  -1

enum src_of_event { NO_SOURCE, SOURCE_MOUSE, SOURCE_KB }; 

int al_inicializacion (int);

void al_finalizacion (void);

/* Funcion get_event
 * 
 * RECIBE: int correspondiente al tipo de input que recibe
 *  1: mouse
 *  2: teclado
 * DEVUELVE: int correspondiente al codigo de la tecla apretada
 *  0: flecha izquierda
 *  1: flecha derercha
 *  2: flecha arriba
 *  3: flecha abajo
 * -1: tecla escape 
 */
int al_get_event (void);

/* Funcion turn_light_on
 * 
 * RECIBE: int de 0 a 4
 *  0: enciende solo la luz izquierda
 *  1: enciende solo la luz derecha
 *  2: enciende solo la luz superior
 *  3: enciende solo la luz inferior
 *  4: apaga todas las luces
 */
void al_turn_light_on (int);

/* Funcion play_beep
 * 
 * RECIBE: int de 0 a 4
 *  0: prende el sonido del boton izquierdo
 *  1: prende el sonido del boton derecho
 *  2: prende el sonido del boton superior
 *  3: prende el sonido del boton inferior
 *  4: silencio
 */
void al_play_beep (int);


/* Funcion kb_or_mouse 
 * 
 * En su primera invocacion, muestra un mensaje en pantalla indicando al usuario
 * que si desea jugar con el teclado, aprete cualquier tecla, y en caso contrario, 
 * para jugar con el mouse, que aprete cualquier boton 
 * 
 * DEVUELVE: el codigo correspondiente a la eleccion del usuario (int):
 *  1: mouse
 *  2: teclado
 * 
 * En las invocaciones siguientes se saltea el mensaje de eleccion. Se devuelve 
 * el codigo correspondiente al metodo de input seleccionado en la primera 
 * invocacion
 */
int al_kb_or_mouse (void);

/* Funcion new_highscore
 * 
 * RECIBE: int con el nuevo highscore
 * 
 * Abre un pop up indicando que se ha llegado a un nuevo highscore y cual es el 
 * valor del mismo.
 * Reproduce musica mientras que el pop up este abierto
 */
void al_new_highscore(int);

/* Funcion wrong_sequence
 * 
 * Lleva a cabo la animacion y reproduce el sonido correspondientes al momento 
 * en el que el usuario ingresa una secuencia incorrecta
 */
void al_wrong_attempt (void);

/* Funcion correct_sequence
 * 
 * Lleva a cabo la animacion y reproduce el sonido correspondientes al momento 
 * en el que el usuario ingresa una secuencia correcta
 */
void al_correct_attempt (void);



void al_update_score(int);


#endif /* AL_DISPLAY_MANAGEMENT_H */