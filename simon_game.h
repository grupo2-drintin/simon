#ifndef SIMON_GAME_H
#define SIMON_GAME_H


#ifndef STATUS_FLAGS
#define STATUS_FLAGS
#define S_ERROR     2
#define S_CONTINUE  1
#define S_GAMEOVER  0
#endif //STATUS FLAGS: indican si el juego termino o no, o si hubo error

int simon_game (void); //devuelve un status flag



#endif /* SIMON_GAME_H */

