#ifndef BACKEND_SIMON_H
#define BACKEND_SIMON_H

#define IO_ALLEGRO  0
#define IO_RPI      1

#define IO          IO_ALLEGRO

#define WRONG_ATTEMPT       0
#define SUCCESSFUL_ATTEMPT  1



enum simon_colors {S_ALL_OFF, S_RED, S_GREEN, S_BLUE, S_YELLOW};

void display_sequence(char_buffer_t sequence);
//decide el intervalo de tiempo de acuardo a n_written


#if IO == IO_ALLEGRO
int user_attempt(char_buffer_t correct_sequence, int event_source);

#else
int user_attempt(char_buffer_t);

#endif //IO


#endif //BACKEND_SIMON_H