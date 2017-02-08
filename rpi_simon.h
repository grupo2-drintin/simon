#ifndef RPI_SIMON_H
#define RPI_SIMON_H

#define EXIT_SIMON -1



int inicializacion(void);

void start_input(void);

int get_event(void);

void stop_input(void);

void finalizacion (void);

void turn_light_on (int);

void correct_attempt(void)

void wrong_sequence(void);


#endif /* RPI_SIMON_H */
