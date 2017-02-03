#ifndef AL_DISPLAY_MANAGEMENT_H
#define AL_DISPLAY_MANAGEMENT_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "al_img_prop.h"
#include <stdio.h>

#define EXIT_SIMON  -1

enum lights { LEFT, RIGHT, TOP, BOTTOM, LIGHTS_OFF }; //quedaria en otro archivo asi lo pueden usar todos los modulos
enum src_of_event { NO_SOURCE, SOURCE_MOUSE, SOURCE_KB }; //source of event, de donde tomar input

int inicializacion (void);

void finalizacion (void);

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
int get_event (int);

/* Funcion turn_light_on
 * 
 * RECIBE: int de 0 a 4
 *  0: enciende solo la luz izquierda
 *  1: enciende solo la luz derecha
 *  2: enciende solo la luz superior
 *  3: enciende solo la luz inferior
 *  4: apaga todas las luces
 */
void turn_light_on (int);

/* Funcion play_beep
 * 
 * RECIBE: int de 0 a 4
 *  0: prende el sonido del boton izquierdo
 *  1: prende el sonido del boton derecho
 *  2: prende el sonido del boton superior
 *  3: prende el sonido del boton inferior
 *  4: silencio
 */
void play_beep (int);

/*
 * 
 */
int kb_or_mouse (void);


#endif /* AL_DISPLAY_MANAGEMENT_H */