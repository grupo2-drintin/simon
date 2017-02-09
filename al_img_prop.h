#ifndef IMG_PROP_H
#define IMG_PROP_H

#define SCREEN_H        780     /* ancho del fondo */
#define SCREEN_W        637     /* altura del fondo */
#define SCREEN_MARGIN   10      /* margen de la pantalla */
#define SIMON_CENTER_X  318     /* eje de simetria de los botones del simon en eje x */
#define SIMON_CENTER_Y  443     /* eje de simetria de los botones del simon en eje y */

#define BUTTON_W        165     /* ancho de los botones */
#define BUTTON_D        127     /* distancia de los botones desde el centro de simetria */
#define SPRITE_H        154     /* altura de los sprites de hongos */

#define FONT_TTF_F      "SuperMario.ttf"    /* nombre del archivo de la fuente */
#define FONT_SIZE       20

#define BACKGROUND_F    "mario_background.png"
#define TOP_SPRITE_F    "blue_mush.png"
#define RIGHT_SPRITE_F  "yellow_mush.png"
#define BOTTOM_SPRITE_F "red_mush.png"
#define LEFT_SPRITE_F   "green_mush.png"

/* coordenadas de la esquina superior izquierda de los botones */
#define LEFT_X    (SIMON_CENTER_X - BUTTON_D - BUTTON_W)
#define LEFT_Y    (SIMON_CENTER_Y - BUTTON_W/2)
#define RIGHT_X   (SIMON_CENTER_X + BUTTON_D)
#define RIGHT_Y   (SIMON_CENTER_Y - BUTTON_W/2)
#define TOP_X     (SIMON_CENTER_X - BUTTON_W/2)
#define TOP_Y     (SIMON_CENTER_Y - BUTTON_D - BUTTON_W)
#define BOTTOM_X  (SIMON_CENTER_X - BUTTON_W/2)
#define BOTTOM_Y  (SIMON_CENTER_Y + BUTTON_D)

#define TOP_BEEP_F      "top_beep.wav"
#define RIGHT_BEEP_F    "right_beep.wav"
#define BOTTOM_BEEP_F   "bottom_beep.wav"
#define LEFT_BEEP_F     "left_beep.wav"
#define HIGHSCORE_MUSIC_F       "mario_star.wav"
#define CORRECT_SEQUENCE_MUSIC_F "coin.wav"
#define CORRECT_SEQUENCE_MUSIC_TIME 0.5         /*duracion de correct sequence music*/
#define WRONG_SEQUENCE_MUSIC_F  "mario_dies.wav"
#define WRONG_SEQUENCE_MUSIC_TIME 3.0           /* duracion de wrong sequence music. 
                                                 * debe ser mayor a 0.2 */


#endif /* IMG_PROP_H */
