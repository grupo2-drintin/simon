#ifndef AL_DISPLAY_MANAGEMENT_H
#define AL_DISPLAY_MANAGEMENT_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "al_img_prop.h"
#include <stdio.h>

enum colores {LEFT, RIGHT, TOP, BOTTOM, LIGHTS_OFF};
//eventualmente esto deberia tener el nombre de los colores

#define EXIT_SIMON  -1  //VALE PONERLE EL VALOR QUE SE LES PLAZCA

static ALLEGRO_DISPLAY *main_display = NULL;        //no se si poner esto aca o en el .c
static ALLEGRO_TIMER *fps_timer = NULL;
static ALLEGRO_BITMAP *simon_background = NULL;
static ALLEGRO_BITMAP *top_light = NULL;
static ALLEGRO_BITMAP *right_light = NULL;
static ALLEGRO_BITMAP *bottom_light = NULL;
static ALLEGRO_BITMAP *left_light = NULL;
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;
static ALLEGRO_EVENT ev;

int inicializacion (void);

/* Funcion get_event()
 * DEVUELVE: int correspondiente al codigo de la tecla apretada
 * Flecha izquierda: 0
 * Flecha derercha:  1
 * Flecha arriba:    2
 * Flecha abajo:     3
 * Tecla escape:     -1
 */
int get_event (void);

/* Funcion turn_light_on:
 * RECIBE: int de 0 a 4
 *  0: enciende solo la luz izquierda
 *  1: enciende solo la luz derecha
 *  2: enciende solo la luz superior
 *  3: enciende solo la luz inferior
 *  4: apaga todas las luces
 */
void turn_light_on (int);
void finalizacion (void);


#endif /* AL_DISPLAY_MANAGEMENT_H */
