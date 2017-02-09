#include "al_display_management.h"
//0043943829

static ALLEGRO_DISPLAY  *main_display = NULL;
static ALLEGRO_TIMER    *fps_timer = NULL;
static ALLEGRO_BITMAP   *simon_background = NULL;
static ALLEGRO_BITMAP   *top_light = NULL;
static ALLEGRO_BITMAP   *right_light = NULL;
static ALLEGRO_BITMAP   *bottom_light = NULL;
static ALLEGRO_BITMAP   *left_light = NULL;
static ALLEGRO_SAMPLE   *top_beep = NULL;
static ALLEGRO_SAMPLE   *right_beep = NULL;
static ALLEGRO_SAMPLE   *bottom_beep = NULL;
static ALLEGRO_SAMPLE   *left_beep = NULL;
static ALLEGRO_SAMPLE   *wrong_sequence_music = NULL;
static ALLEGRO_SAMPLE   *correct_sequence_music = NULL;
static ALLEGRO_SAMPLE   *highscore_music = NULL;
static ALLEGRO_FONT     *font = NULL;
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;


static int highscore = 0;
static int score = 0;

int inicializacion(int old_highscore)
{
    highscore = old_highscore;
    
    if(!al_init())
    {
        fprintf(stderr, "Unable to start allegro\n");
        return -1;
    }
    if( !al_install_keyboard()) 
    {
        fprintf(stderr, "Unable to initialize the keyboard!\n");
        al_uninstall_system();
        return -1;
    }
    
    else if( !al_init_image_addon())
    {
        fprintf(stderr,"Unable to start image addon \n"); 
        al_uninstall_system();
        return -1;
    }
    else if( !(main_display = al_create_display(SCREEN_W, SCREEN_H)) )
    {
            fprintf(stderr,"Unable to create display\n"); 
            al_shutdown_image_addon();
            al_uninstall_system();
            return -1;
    }
    else if( !(simon_background = al_load_bitmap(BACKGROUND_F)) )
    {
        fprintf(stderr,"Unable to load background\n"); 
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_uninstall_system();
        return -1;
    }
    else if( !(top_light = al_load_bitmap(TOP_SPRITE_F)) )
    {
        fprintf(stderr,"Unable to load top sprite\n"); 
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_uninstall_system();
        return -1;
    }   
    else if( !(right_light = al_load_bitmap(RIGHT_SPRITE_F)) )
    {
        fprintf(stderr,"Unable to load right sprite\n"); 
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_uninstall_system();
        return -1;
    }
    else if( !(bottom_light = al_load_bitmap(BOTTOM_SPRITE_F)) )
    {
        fprintf(stderr,"Unable to load bottom sprite\n"); 
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_uninstall_system();
        return -1;
    }   
    else if( !(left_light = al_load_bitmap(LEFT_SPRITE_F)) )
    {
        fprintf(stderr,"Unable to load left sprite\n"); 
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_uninstall_system();
        return -1;
    }   
    else if(!al_install_audio())
    {
        fprintf(stderr, "Unable to initialize audio\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_uninstall_system();
        return -1;
    }   
    else if(!al_init_acodec_addon())
    {
        fprintf(stderr, "Unable to initialize audio codecs\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_uninstall_audio();
        al_uninstall_system();
        return -1;
    }
    else if ( !al_reserve_samples(1) )
    {
        fprintf(stderr, "Unable to reserve sample\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_uninstall_audio();
        al_uninstall_system();
        return -1;
    }
    else if( !(wrong_sequence_music = al_load_sample(WRONG_SEQUENCE_MUSIC_F )))
    {
        fprintf(stderr, "Unable to load wrong sequence music\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_uninstall_audio();
        al_uninstall_system();
        return -1;
    }
    else if( !(correct_sequence_music = al_load_sample(CORRECT_SEQUENCE_MUSIC_F )))
    {
        fprintf(stderr, "Unable to load correct sequence music\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_destroy_sample(wrong_sequence_music);
        al_uninstall_audio();
        al_uninstall_system();
        return -1;
    }
    else if( !(top_beep = al_load_sample(TOP_BEEP_F )))
    {
        fprintf(stderr, "Unable to load top beep sample\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_destroy_sample(wrong_sequence_music);
        al_destroy_sample(correct_sequence_music);
        al_uninstall_audio();
        al_uninstall_system();
        return -1;
    }
    else if( !(right_beep = al_load_sample(RIGHT_BEEP_F )))
    {
        fprintf(stderr, "Unable to load right beep sample\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_destroy_sample(wrong_sequence_music);
        al_destroy_sample(correct_sequence_music);
        al_destroy_sample(top_beep);
        al_uninstall_audio();
        al_uninstall_system();
        return -1;
    }
    else if( !(bottom_beep = al_load_sample(BOTTOM_BEEP_F )))
    {
        fprintf(stderr, "Unable to load bottom beep\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_destroy_sample(wrong_sequence_music);
        al_destroy_sample(correct_sequence_music);
        al_destroy_sample(top_beep);
        al_destroy_sample(right_beep);
        al_uninstall_audio();
        al_uninstall_system();
        return -1;
    }
    else if( !(left_beep = al_load_sample(LEFT_BEEP_F) ) )
    {
        fprintf(stderr, "Unable to load left beep\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_destroy_sample(wrong_sequence_music);
        al_destroy_sample(correct_sequence_music);
        al_destroy_sample(top_beep);
        al_destroy_sample(right_beep);
        al_destroy_sample(bottom_beep);
        al_uninstall_audio();
        al_uninstall_system();
        return -1;
    }
    else if( !(highscore_music = al_load_sample(HIGHSCORE_MUSIC_F) ) )
    {
        fprintf(stderr, "Unable to load highscore music\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_destroy_sample(wrong_sequence_music);
        al_destroy_sample(correct_sequence_music);
        al_destroy_sample(top_beep);
        al_destroy_sample(right_beep);
        al_destroy_sample(bottom_beep);
        al_destroy_sample(left_beep);
        al_uninstall_audio();
        al_uninstall_system();
        return -1;
    }
    else if( !(event_queue = al_create_event_queue()))
    {
        fprintf(stderr, "Unable to create event queue\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_destroy_sample(wrong_sequence_music);
        al_destroy_sample(correct_sequence_music);
        al_destroy_sample(top_beep);
        al_destroy_sample(right_beep);
        al_destroy_sample(bottom_beep);
        al_destroy_sample(left_beep);
        al_destroy_sample(highscore_music);
        al_uninstall_audio();
        al_uninstall_system();
        return -1;
    }   

    if(!al_init_native_dialog_addon()) 
    {
        fprintf(stderr, "Unable to initialize the native dialog addon\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_destroy_sample(wrong_sequence_music);
        al_destroy_sample(correct_sequence_music);
        al_destroy_sample(top_beep);
        al_destroy_sample(right_beep);
        al_destroy_sample(bottom_beep);
        al_destroy_sample(left_beep);
        al_destroy_event_queue(event_queue);
        al_destroy_sample(highscore_music);
        al_uninstall_audio();
        al_uninstall_system();
        return -1;
    }
    if(!al_install_mouse()) 
    {
        fprintf(stderr, "Unable to initialize the mouse\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_destroy_sample(wrong_sequence_music);
        al_destroy_sample(correct_sequence_music);
        al_destroy_sample(top_beep);
        al_destroy_sample(right_beep);
        al_destroy_sample(bottom_beep);
        al_destroy_sample(left_beep);
        al_destroy_sample(highscore_music);
        al_destroy_event_queue(event_queue);
        al_uninstall_audio();
        al_uninstall_system();
        return -1;
    }

    al_init_font_addon();
    al_init_ttf_addon();
    
    if ( !( font = al_load_ttf_font(FONT_TTF_F, 20,0) ) )
    {
        fprintf(stderr, "Unable to load font\n");
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_destroy_sample(wrong_sequence_music);
        al_destroy_sample(correct_sequence_music);
        al_destroy_sample(top_beep);
        al_destroy_sample(right_beep);
        al_destroy_sample(bottom_beep);
        al_destroy_sample(left_beep);
        al_destroy_sample(highscore_music);
        al_destroy_event_queue(event_queue);
        al_uninstall_audio();
        al_uninstall_system();
        return -1;
    }
    
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(main_display));
    
    return 0;
}

void finalizacion(void)
{
    al_shutdown_image_addon();
    al_destroy_display(main_display);
    al_destroy_bitmap(simon_background);
    al_destroy_bitmap(top_light);
    al_destroy_bitmap(right_light);
    al_destroy_bitmap(bottom_light);
    al_destroy_bitmap(left_light);
    al_destroy_sample(wrong_sequence_music);
    al_destroy_sample(correct_sequence_music);
    al_destroy_sample(top_beep);
    al_destroy_sample(right_beep);
    al_destroy_sample(bottom_beep);
    al_destroy_sample(left_beep);
    al_destroy_sample(highscore_music);
    al_destroy_event_queue(event_queue);
    al_uninstall_audio();
    al_uninstall_system();
}

int get_event(void)
{
    ALLEGRO_EVENT ev;   /* Contiene los eventos captados */
    
    /* event codes: -1 escape, 0 a 3 botones del simon */
    int event_code = LIGHTS_OFF;            /* "Resetear" event_code para que no adopte el valor de un boton por casualidad */  
    int source_of_event = kb_or_mouse();    /* indicar si se debe leer del teclado o del mouse*/
    
    while(  (event_code != EXIT_SIMON)      /* buscar eventos hasta que se aprete un boton del simon o se cierre el programa */
         && (event_code != LEFT)
         && (event_code != RIGHT)
         && (event_code != TOP)
         && (event_code != BOTTOM))
    {    
        al_wait_for_event(event_queue, &ev);
   
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            event_code = EXIT_SIMON;
        }
        else if ((source_of_event == SOURCE_KB) && (ev.type == ALLEGRO_EVENT_KEY_UP))
        {
            /*  los codigos de allegro para las teclas izq, der, arriba y abajo
             *  son entero sucesivos en ese mismo orden */
            if ( ev.keyboard.keycode >= ALLEGRO_KEY_LEFT  
              && ev.keyboard.keycode <= ALLEGRO_KEY_DOWN )

            /*  al restarle ALLEGRO_KEY_LEFT, los codigos quedan:
             *  tecla izq: 0
             *  tecla der: 1
             *  tecla arriba: 2
             *  tecla abajo: 3 
             */       
            {
                event_code = ev.keyboard.keycode - ALLEGRO_KEY_LEFT; 
            }
            else if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
                event_code = EXIT_SIMON;
            }
        }
        else if ((source_of_event == SOURCE_MOUSE) && (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP))
        {
//            fprintf(stderr,"x = %d, y = %d, dx = %d, dy = %d\n", ev.mouse.x, ev.mouse.y, ev.mouse.dx, ev.mouse.dy);            
            if( ( ( LEFT_X <= ev.mouse.x ) && ( ev.mouse.x <= ( LEFT_X + BUTTON_W)) )
             && ( ( LEFT_Y <= ev.mouse.y ) && ( ev.mouse.y <= ( LEFT_Y + BUTTON_W)) ))
             /* Si se suelta el boton del mouse dentro del boton izquierdo del simon */
            {
                event_code = LEFT;
            }
            else if( ( ( RIGHT_X <= ev.mouse.x ) && ( ev.mouse.x <= ( RIGHT_X + BUTTON_W)) )
                  && ( ( RIGHT_Y <= ev.mouse.y ) && ( ev.mouse.y <= ( RIGHT_Y + BUTTON_W)) ))
             /* Si se suelta el boton del mouse dentro del boton derecho del simon */
            {
                event_code = RIGHT;
            }
            else if( ( ( TOP_X <= ev.mouse.x ) && ( ev.mouse.x <= ( TOP_X + BUTTON_W)) )
                  && ( ( TOP_Y <= ev.mouse.y ) && ( ev.mouse.y <= ( TOP_Y + BUTTON_W)) ))
             /* Si se suelta el boton del mouse dentro del boton de arriba del simon */
            {
                event_code = TOP;
            }
            else if( ( ( BOTTOM_X <= ev.mouse.x ) && ( ev.mouse.x <= ( BOTTOM_X + BUTTON_W)) )
                  && ( ( BOTTOM_Y <= ev.mouse.y ) && ( ev.mouse.y <= ( BOTTOM_Y + BUTTON_W)) ))
             /* Si se suelta el boton del mouse dentro del boton de abajo del simon */
            {
                event_code = BOTTOM;
            }
        }
    }
    return (event_code);
}

void play_beep(int button)
{
    al_stop_samples();  /* si esta sonando algun tono, deja de sonar */
    
    switch (button)
    /* Reproducir el tono correspondiente al boton presionado */
    {
        case LEFT:              
        {
            al_play_sample(left_beep, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
            break;
        }
        case RIGHT:
        {
            al_play_sample(right_beep, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
            break;
        }
        case TOP:
        {
            al_play_sample(top_beep, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
            break;
        }
        case BOTTOM:
        {
            al_play_sample(bottom_beep, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);
            break;
        }
        defalut:
            break;
        /* No es necesario hacer un caso para LIGHTS_OFF ya que para todos los 
         * casos se deja de reproducir el beep que estaba sonando anteriormente */
    }
}

void turn_light_on (int button)
{
    /* al dibujar solo el fondo, se "apagan" todos los botones */
    draw_background_and_scores();  
    
    /* "encender" el boton presionado */ 
    switch (button)
    {
        case LEFT:
            al_draw_bitmap(left_light, LEFT_X, LEFT_Y - SPRITE_H, 0);
            break;
        case RIGHT:
            al_draw_bitmap(right_light, RIGHT_X, RIGHT_Y - SPRITE_H, 0);
            break;
        case TOP:
            al_draw_bitmap(top_light, TOP_X, TOP_Y - SPRITE_H, 0);
            break;
        case BOTTOM:
            al_draw_bitmap(bottom_light, BOTTOM_X, BOTTOM_Y - SPRITE_H, 0);
            break;
        default:
            break;
        /* No es necesario hacer un case para LIGHTS_OFF, ya que en ese caso no se carga
         * ningun bitmap ademas del fondo */
    }
    
    /* Pasar lo dibujado a la pantalla */
    al_flip_display();  
}

int kb_or_mouse (void)
{
    
    static int source_of_events = NO_SOURCE;
    ALLEGRO_EVENT ev;   /* Contiene los eventos captados */
    
    /* Solo se entra en la primera invocacion ya que ahi se elige mouse o teclado*/
    while ( source_of_events == NO_SOURCE ) 
    {
        al_draw_text( font, al_map_rgb(255,255,255), (TOP_X + SCREEN_MARGIN), (SCREEN_MARGIN + FONT_SIZE*0), ALLEGRO_ALIGN_LEFT, " To play with the keyboard" );
        al_draw_text( font, al_map_rgb(255,255,255), (TOP_X + SCREEN_MARGIN), (SCREEN_MARGIN + FONT_SIZE*1), ALLEGRO_ALIGN_LEFT, "press any key" );
        al_draw_text( font, al_map_rgb(255,255,255), (TOP_X + SCREEN_MARGIN), (SCREEN_MARGIN + FONT_SIZE*2), ALLEGRO_ALIGN_LEFT, " To play with the mouse" );
        al_draw_text( font, al_map_rgb(255,255,255), (TOP_X + SCREEN_MARGIN), (SCREEN_MARGIN + FONT_SIZE*3), ALLEGRO_ALIGN_LEFT, "click it" );
        al_flip_display();
        
        al_wait_for_event(event_queue, &ev);
                
        if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            
            source_of_events = SOURCE_KB;
            draw_background_and_scores();
            al_draw_text( font, al_map_rgb(255,255,255), (TOP_X + SCREEN_MARGIN), (SCREEN_MARGIN + FONT_SIZE), ALLEGRO_ALIGN_LEFT, "Keyboard selected" );
            al_flip_display();
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            source_of_events = SOURCE_MOUSE;
            draw_background_and_scores();
            al_draw_text( font, al_map_rgb(255,255,255), (TOP_X + SCREEN_MARGIN), (SCREEN_MARGIN + FONT_SIZE), ALLEGRO_ALIGN_LEFT, "mouse selected" );
            al_flip_display();
        }
    }
    /* Una vez que el usuario elige mouse o teclado, siempre se devuelve el codigo correspondiente a su eleccion */
    return source_of_events;    
}

void new_highscore(int new_highscore)
{    
    highscore = new_highscore;      /* actualizar el highscore */
    
    ALLEGRO_SAMPLE_ID highscore_music_id;
    
    al_play_sample( highscore_music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &highscore_music_id );
    
    /* Crear un arreglo de char con los ascii del highscore */
    char hs_value[4];
    snprintf( hs_value, sizeof(hs_value), "%d", highscore );
    
    /* Crear un arreglo de char con el mensaje */
    char hs_word[250];
    strncpy( hs_word, "Your new highscore is " , 250);
        
    /* Unir los dos arreglos, importante que el primer arreglo tenga suficiente 
     * tamano como para contenter a los dos juntos */ 
    char * hs_final = strncat( hs_word , hs_value , 250 - strlen(hs_word) );
    
    /* Crear un pop up con el mensaje del nuevo highscore */
    al_show_native_message_box(
    NULL,
    "New highscore",
    "Congratulations!",
    hs_final,
    "close",
    ALLEGRO_MESSAGEBOX_OK_CANCEL
    );
    
    /* Una vez cerrado el pop up, detener la musica */
    al_stop_sample( &highscore_music_id );
}    

void wrong_sequence ( void )
{
    al_play_sample( wrong_sequence_music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL );
    int i;
    for ( i = WRONG_SEQUENCE_MUSIC_TIME/0.2 ; i > 0 ; i-- )
    /* Prender y apagar todos los botones hasta que se termine la musica */
    {
        draw_background_and_scores();
        al_draw_bitmap(left_light, LEFT_X, LEFT_Y - SPRITE_H, 0);
        al_draw_bitmap(right_light, RIGHT_X, RIGHT_Y - SPRITE_H, 0);
        al_draw_bitmap(top_light, TOP_X, TOP_Y - SPRITE_H, 0);
        al_draw_bitmap(bottom_light, BOTTOM_X, BOTTOM_Y - SPRITE_H, 0);
        al_flip_display();
        al_rest(0.1);
        
        draw_background_and_scores();  
        al_flip_display();
        al_rest(0.1);
    }
}

void correct_sequence ( void )
{
    al_play_sample( correct_sequence_music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL );
    
    draw_background_and_scores();  
    al_draw_bitmap(left_light, LEFT_X, LEFT_Y - SPRITE_H, 0);
    al_flip_display();
    al_rest(CORRECT_SEQUENCE_MUSIC_TIME/4);
    al_draw_bitmap(top_light, TOP_X, TOP_Y - SPRITE_H, 0);
    al_flip_display();
    al_rest(CORRECT_SEQUENCE_MUSIC_TIME/4);
    al_draw_bitmap(right_light, RIGHT_X, RIGHT_Y - SPRITE_H, 0);
    al_flip_display();
    al_rest(CORRECT_SEQUENCE_MUSIC_TIME/4);
    al_draw_bitmap(bottom_light, BOTTOM_X, BOTTOM_Y - SPRITE_H, 0);
    al_flip_display();
    al_rest(CORRECT_SEQUENCE_MUSIC_TIME/4);
    
    /* Poner en display solo el fondo por medio segundo 
     * para que sea claro cuando cominenza la nueva 
     * secuencia */
    draw_background_and_scores();  
    al_flip_display();
    al_rest(0.5);
}

void draw_background_and_scores ()
{
    al_draw_bitmap(simon_background, 0, 0, 0);  /* dibujar el fondo */

    /* Crear un arreglo de char con los ascii del highscore */
    char hs_value[4];
    snprintf( hs_value, sizeof(hs_value), "%d", highscore );

    /* Crear un arreglo de char con los ascii de la palabra HIGHSCORE */
    char hs_word[250];
    strncpy( hs_word, "HIGHSCORE: ", 250);  
    
    /* Unir los dos arreglos, importante que el primer arreglo tenga suficiente 
     * tamano como para contenter a los dos juntos */ 
    char * hs_final = strncat( hs_word, hs_value, 250 - strlen(hs_word) );  
    
    /* Dibujar el highscore */
    al_draw_text( font, al_map_rgb(255,255,255), (SCREEN_MARGIN), (SCREEN_MARGIN + FONT_SIZE), ALLEGRO_ALIGN_LEFT, hs_final );
   
/* Repetir el procedimiento para el score actual */
    
    char s_value[4];
    snprintf( s_value, sizeof(s_value), "%d", score );
   
    char s_word[19];
    strncpy( s_word, "CURRENT SCORE: ", 250);
    
    char * s_final = strncat( s_word, s_value, 250 - strlen(s_word) );
    
    al_draw_text( font, al_map_rgb(255,255,255), (SCREEN_MARGIN), (SCREEN_MARGIN), ALLEGRO_ALIGN_LEFT, s_final );

/* NOTA: esta funcion no los pone en pantalla, 
 * solo los carga para que aparezcan cuando se 
 * invoque a al_flip_display() */
}

void update_score( int new_score )
{
    score = new_score;
}