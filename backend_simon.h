#ifndef BACKEND_SIMON_H
#define BACKEND_SIMON_H

enum simon_colors {S_ALL_OFF, S_RED, S_GREEN, S_BLUE, S_YELLOW};


void display_sequence(char_buffer_t, int); //decide el intervalo de tiempo de
//acuardo a n_written


int user_attempt(char_buffer_t);
#define WRONG_ATTEMPT       0
#define SUCCESSFUL_ATTEMPT  1

#endif //BACKEND_SIMON_H