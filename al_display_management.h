#ifndef AL_DISPLAY_MANAGEMENT_H
#define AL_DISPLAY_MANAGEMENT_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_audio.h"
#include "allegro5/allegro_acodec.h"
#include "allegro5/allegro_font.h" //manejo de fonts
#include "allegro5/allegro_ttf.h" //Manejo de ttfs
#include "allegro5/allegro_native_dialog.h" //Manejo de ttfs
#include "al_img_prop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SIMON  -1

enum src_of_event { NO_SOURCE, SOURCE_MOUSE, SOURCE_KB }; //source of event, de donde tomar input

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

/*
 * 
 */
int al_b_or_mouse (void);

/* Funcion new_highscore
 * 
 * RECIBE: int con el nuevo highscore
 * Abre un pop up indicando que se ha llegado
 * a un nuevo highscore y cual es el valor 
 * del mismo
 */
void al_new_highscore(int);

/* Funcion show_highscore
 * 
 * Carga en el display principal
 * cual es el highscore actual
 * (no lo muestra, solamente lo 
 * carga. Para mostrarlo, es 
 * necesario invocar a la funcion
 * al_flip_display(). )
 */
void draw_score_and_highscore ();

/* Funcion wrong_sequence
 * 
 * Lleva a cabo la animacion y 
 * reproduce el sonido correspondientes
 * a una secuencia incorrecta 
 * sincronizadamente
 */
void al_wrong_attempt (void);

/* Funcion correct_sequence
 * 
 * Lleva a cabo la animacion y 
 * reproduce el sonido correspondientes
 * a una secuencia correcta sincronizadamente
 */
void al_correct_attempt (void);

void draw_bg_and_hs (void);  

void al_update_score(int);


#endif /* AL_DISPLAY_MANAGEMENT_H */