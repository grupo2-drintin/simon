#ifndef IMG_PROP_H
#define IMG_PROP_H

#define SCREEN_H        1114            //ancho del fondo
#define SCREEN_W        910             //altura del fondo
#define SCREEN_CENTER_X (SCREEN_W/2)    //posicion del centro de pantalla en eje X
#define SCREEN_CENTER_Y (SCREEN_H/2)    //posicion del centro de pantalla en eje Y

#define SPRITE_W        128             //ancho de los sprites de botones
#define SPRITE_DISTANCE 150             //distancia de los botones desde el centro de pantalla

#define BACKGROUND_F    "simon_background.png"
#define TOP_SPRITE_F    "top_light.png"
#define RIGHT_SPRITE_F  "right_light.png"
#define BOTTOM_SPRITE_F "bottom_light.png"
#define LEFT_SPRITE_F   "left_light.png"

#define LEFT_X    (SCREEN_CENTER_X - SPRITE_DISTANCE - SPRITE_W/2)
#define LEFT_Y    (SCREEN_CENTER_Y - SPRITE_W/2)
#define RIGHT_X   (SCREEN_CENTER_X + SPRITE_DISTANCE - SPRITE_W/2)
#define RIGHT_Y   (SCREEN_CENTER_Y - SPRITE_W/2)
#define TOP_X     (SCREEN_CENTER_X - SPRITE_W/2)
#define TOP_Y     (SCREEN_CENTER_Y - SPRITE_DISTANCE - SPRITE_W/2)
#define BOTTOM_X  (SCREEN_CENTER_X - SPRITE_W/2)
#define BOTTOM_Y  (SCREEN_CENTER_Y + SPRITE_DISTANCE - SPRITE_W/2)

#define TOP_BEEP_F      "top_beep.wav"
#define RIGHT_BEEP_F    "right_beep.wav"
#define BOTTOM_BEEP_F   "bottom_beep.wav"
#define LEFT_BEEP_F     "left_beep.wav"
#define WRONG_SEQUENCE_MUSIC_F  "mario_dies.wav"
#define WRONG_SEQUENCE_MUSIC_TIME 3.0               //duracion de wrong sequence music
#define CORRECT_SEQUENCE_MUSIC_F "coin.wav"
#define CORRECT_SEQUENCE_MUSIC_TIME 0.5             //duracion de correct sequence music


#endif /* IMG_PROP_H */
