
/* 
 * File:   main_simon.c
 * Author: rochi
 *
 * Created on February 6, 2017, 4:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "simon_game.h"

/*
 * 
 */
int main(int argc, char** argv) {

    if(simon_game()==S_ERROR)
    {printf("simon devolvio error!!\n\n");}    
    
    return (EXIT_SUCCESS);
}

