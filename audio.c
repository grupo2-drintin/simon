
/* Sonido para el Simon*/
// gcc audio.c libaudio.c -I/usr/local/include -L/usr/local/lib -lSDL -o audio -lpthread
// Run with ./simple1


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "libaudio.h"
#include "audio.h"
#include "backend_simon.h"

#define PLAY_TIME 1

void play_color(char * AudioFile);
void wrong_sequence(void);


char AudioFile_RED[]="./Sound/red.wav";
char AudioFile_GREEN[]="./Sound/green.wav";
char AudioFile_BLUE[]="./Sound/blue.wav";
char AudioFile_YELLOW[]="./Sound/yellow.wav";
char AudioFile_BUZZ[]="./Sound/buzz.wav";



void play_beep(int color)
{
	
    
    
	switch (color)
	{
		case YELLOW: 
		{	play_color(AudioFile_YELLOW); 	
		}
                break;
		case RED:
		{	play_color(AudioFile_RED); 			  // Waste some time while playing
   	    	}
                break;
		case GREEN:
		{	play_color(AudioFile_GREEN); 		  // Waste some time while playing
   	    	}
                break;
		case BLUE:
		{	play_color(AudioFile_BLUE); 		  // Waste some time while playing
   	    	}
                break;
		case LIGHTS_OFF:
		{	end_play(); 				  // Waste some time while playing
   	    	}
                break;
            case GAMEOVER_SOUND:
                {       play_color(AudioFile_BUZZ);
                }
                break;
	}
}

void play_color(char * AudioFile) // Non blocking Audio File
{
	
 	stop_sound();						  // stop previous audio track (Just in case)
 	
	if(player_status()==READY)
	{
			
	//	printf(GREEN_TEXT "Playing: %s \n",AudioFile); 	printf(WHITE_TEXT);
	
		set_file_to_play(AudioFile);      // Load file 			
	
		play_sound(); 					  // Play File (Non Blocking)
                

		return;
	}
	else
	{
			
		printf(RED_TEXT "System not ready did you run init_sound() ? \n" WHITE_TEXT );
				
		exit(-1);		
	}
	
}




void do_something(void)
{
	int i;
				
	for(i=0;i<PLAY_TIME;i++)  // Do someting else for a while (change i)
	{
		
		/*printf(YELLOW_TEXT "Playing ...\n" WHITE_TEXT ); // show this every 300 ms while playing the sound in background*/
		/*No es necesario el printf, a menos que se necesite ver el estado en la terminal de la rpi*/
	    SDL_Delay(300);
	}
	
	stop_sound();
}

