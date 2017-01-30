#include <stdlib.h>
#include <stdio.h>
#include "char_buffer.h"
#include "backend_simon.h"

#ifndef STATUS_FLAGS
#define STATUS_FLAGS
#define S_ERROR     2
#define S_CONTINUE  1
#define S_GAMEOVER  0
#endif //STATUS FLAGS

#define CB_INIT_SIZE 200    //Tamano inicial del buffer




int simon_game (void)
{
    static FILE f_highscore;
    int highscore;
    int current_score = 0;
    int status = S_CONTINUE;
    
    char_buffer_t correct_sequence = create_cb(CB_INIT_SIZE);    

    
    if((f_highscore = fopen("highscores.txt", "r")) == NULL )
    {
        status = S_ERROR;
    } 
    else
    {
        fscanf (f_highscore, "%d", &highscore);
        fclose (f_highscore);
    }
    
  
    while (status == S_CONTINUE)  
    {
        srand(__TIME__);
        write_cb(&correct_sequence, (char)(rand()%4));
        display_sequence(correct_sequence);
        
        if (user_attempt(correct_sequence) == WRONG_ATTEMPT)
        {   
            status = S_GAMEOVER;
        }    
        else
        {
            if (++current_score >= highscore)
            {
                highscore = current_score;
            }    
        }
    }
    
    if((f_highscore = fopen("highscores.txt", "w")) == NULL )
    {
        status = S_ERROR;
    } 
    else
    {
        fprintf(f_highscore, "%d", highscore);
        fclose(f_highscore);
    }
    
    return status;
}