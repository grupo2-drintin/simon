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
static ALLEGRO_SAMPLE   *losing_music = NULL;
static ALLEGRO_FONT     *font = NULL;
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;
static ALLEGRO_EVENT ev;

int inicializacion(void)
{
    if(!al_init())
    {
            fprintf(stderr, "Unable to start allegro\n");
            return -1;
    }
    al_init_font_addon();       // initialize the font addon
    al_init_ttf_addon();        // initialize the ttf (True Type Font) addon
    
    if( !al_install_keyboard()) 
    {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
    }
    else if( !al_init_image_addon())
    {
            fprintf(stderr,"Unable to start image addon \n"); //Igual que printf pero imprime al error std 
            al_uninstall_system();
            return -1;
    }
    else if( !(main_display = al_create_display(SCREEN_W, SCREEN_H)) )
    {
            fprintf(stderr,"Unable to create display\n"); 
            al_uninstall_system();
            al_shutdown_image_addon();
            return -1;
    }
    else if( !(simon_background = al_load_bitmap(BACKGROUND_F)) )
    {
        fprintf(stderr,"Unable to load background\n"); 
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        return -1;
    }
    else if( !(top_light = al_load_bitmap(TOP_SPRITE_F)) )
    {
        fprintf(stderr,"Unable to load top sprite\n"); 
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        return -1;
    }   
    else if( !(right_light = al_load_bitmap(RIGHT_SPRITE_F)) )
    {
        fprintf(stderr,"Unable to load right sprite\n"); 
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        return -1;
    }
    else if( !(bottom_light = al_load_bitmap(BOTTOM_SPRITE_F)) )
    {
        fprintf(stderr,"Unable to load bottom sprite\n"); 
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        return -1;
    }   
    else if( !(left_light = al_load_bitmap(LEFT_SPRITE_F)) )
    {
        fprintf(stderr,"Unable to load left sprite\n"); 
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        return -1;
    }   
    else if(!al_install_audio())
    {
        fprintf(stderr, "failed to initialize audio\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        return -1;
    }   
    else if(!al_init_acodec_addon())
    {
        fprintf(stderr, "failed to initialize audio codecs\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_uninstall_audio();
        return -1;
    }
    else if ( !al_reserve_samples(1) )
    {
        fprintf(stderr, "failed to reserve samples\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_uninstall_audio();
        return -1;
    }
    else if( !(losing_music = al_load_sample(LOSING_MUSIC_F )))
    {
        fprintf(stderr, "failed to load losing_music\n");
    }
    else if( !(top_beep = al_load_sample("top_beep.wav" )))
    {
        fprintf(stderr, "failed to load top beep\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_uninstall_audio();
    }
    else if( !(right_beep = al_load_sample("right_beep.wav" )))
    {
        fprintf(stderr, "failed to load right beep\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_uninstall_audio();
        al_destroy_sample(top_beep);
    }
    else if( !(bottom_beep = al_load_sample("bottom_beep.wav" )))
    {
        fprintf(stderr, "failed to load bottom beep\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_uninstall_audio();
        al_destroy_sample(top_beep);
        al_destroy_sample(right_beep);
    }
    else if( !(left_beep = al_load_sample("left_beep.wav" )))
    {
        fprintf(stderr, "failed to load left beep\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_uninstall_audio();
        al_destroy_sample(top_beep);
        al_destroy_sample(right_beep);
        al_destroy_sample(bottom_beep);
    }
    else if( !(event_queue = al_create_event_queue()))
    {
        fprintf(stderr, "failed to create event queue\n");
        al_uninstall_system();
        al_shutdown_image_addon();
        al_destroy_display(main_display);
        al_destroy_bitmap(simon_background);
        al_destroy_bitmap(top_light);
        al_destroy_bitmap(right_light);
        al_destroy_bitmap(bottom_light);
        al_destroy_bitmap(left_light);
        al_uninstall_audio();
        al_destroy_sample(top_beep);
        al_destroy_sample(right_beep);
        al_destroy_sample(bottom_beep);
        al_destroy_sample(left_beep);
        return -1;
    }   

    if(!al_init_native_dialog_addon()) 
    {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
    }
    if(!al_install_mouse()) 
    {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
    }
    
    font = al_load_ttf_font("SuperMario.ttf",36,0 ); //HAY CREAR UN FONT PARA CADA TAMAÑO DE LETRA :( 
 
    if (!font)
    {
        fprintf(stderr, "Could not load 'SuperMario.ttf'\n");
        return -1;
    }
    
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(main_display));
    
    al_draw_bitmap(simon_background, 0, 0, 0);
    al_flip_display();
        
    
}

void finalizacion (void)
{
    al_destroy_display(main_display);
    al_destroy_bitmap(simon_background);
    al_destroy_bitmap(left_light);
    al_destroy_bitmap(right_light);
    al_destroy_bitmap(top_light);
    al_destroy_bitmap(bottom_light);
    al_destroy_event_queue(event_queue);
    al_uninstall_audio();
    al_uninstall_mouse();
    al_destroy_sample(right_beep);      //DA SEGMENTATION FAULT Y NO SE POR KE
    al_destroy_sample(left_beep);       //DA SEGMENTATION FAULT Y NO SE POR KE
    al_destroy_sample(top_beep);        //DA SEGMENTATION FAULT Y NO SE POR KE
    al_destroy_sample(bottom_beep);     //DA SEGMENTATION FAULT Y NO SE POR KE
}

int get_event (int source_of_event)
{
    int event_code;     /* -1 escape, 0 a 3 botones del simon */
    
    /*  Esperar eventos hasta que, si se esta usando el teclado, se levante una tecla 
     *  o si se esta usando el mouse, se levante un boton del mouse */
    do
    {
        al_wait_for_event(event_queue, &ev);
    }
    while 
    (  (((source_of_event == SOURCE_MOUSE) && (ev.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP)) 
    || ((source_of_event == SOURCE_KB) && (ev.type != ALLEGRO_EVENT_KEY_DOWN))) 
    && (ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE) );

    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        fprintf(stderr, "entro en display close\n");
        event_code = EXIT_SIMON;
    }
    else if (source_of_event == SOURCE_KB)
    {
        fprintf(stderr, "entro en source_kb");
        fprintf(stderr, "tomo como source al kb\n");
        /*  los codigos de allegro para las teclas izq, der, arriba y abajo
         *  son entero sucesivos en ese mismo orden 
         */
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
    else
    {
        fprintf(stderr, "entro en source_mouse");
        fprintf(stderr,"x = %d, y = %d, dx = %d, dy = %d\n", ev.mouse.x, ev.mouse.y, ev.mouse.dx, ev.mouse.dy);
    }
    fprintf(stderr, "event_code = %d", event_code);
    return (event_code);
}

void play_beep (int button)
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
    al_draw_bitmap(simon_background, 0, 0, 0);  /* al dibujar solo el fondo, se "apagan" todos los botones */
    
    switch (button)
    /* "enciende" el boton presionado */ 
    {
        case LEFT:
        {
            al_draw_bitmap(left_light, LEFT_X, LEFT_Y, 0);
            break;
        }
        case RIGHT:
        {
            al_draw_bitmap(right_light, RIGHT_X, RIGHT_Y, 0);
            break;
        }
        case TOP:
        {
            al_draw_bitmap(top_light, TOP_X, TOP_Y, 0);
            break;
        }
        case BOTTOM:
        {
            al_draw_bitmap(bottom_light, BOTTOM_X, BOTTOM_Y, 0);
            break;
        }
        default:
            break;
        /* No es necesario hacer un case para LIGHTS_OFF, ya que en ese caso no se carga
         * ningun bitmap ademas del fondo */
    }
    al_flip_display();
}

int kb_or_mouse (void)
{
    int source_of_events = NO_SOURCE;
    
    while ( source_of_events == NO_SOURCE )
    {
        al_wait_for_event(event_queue, &ev);
                
        if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            source_of_events = SOURCE_KB;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            source_of_events = SOURCE_MOUSE;
        }
    }
    return source_of_events;
}

void new_highscore( int highscore )
{
    char hs_value[4];
    sprintf( hs_value, "%d", highscore );
    char hs_word[15];
    strcpy( hs_word, "Your new highscore is ");
    
    char * hs_final = strcat( hs_word , hs_value );
    
    al_show_native_message_box(
    main_display,
    "New highscore",
    "Congratulations!",
    hs_final,
    "close",
    ALLEGRO_MESSAGEBOX_OKCANCEL
    );
}    
    
void show_highscore( int highscore )
{    
    char hs_value[4];
    sprintf( hs_value, "%d", highscore );
   
    char hs_word[15];
    strcpy( hs_word, "HIGHSCORE: ");
    
    char * hs_final = strcat( hs_word , hs_value );
    
    al_draw_text( font, al_map_rgb(255,255,255), SCREEN_W/4, (SCREEN_H/8), ALLEGRO_ALIGN_CENTER, hs_final );
    al_flip_display();
 }

void wrong_sequence ( void )
{
    al_play_sample( losing_music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL );
    int i;
    for ( i = LOSING_MUSIC_TIME/0.2 ; i > 0 ; i-- )
    {
        al_draw_bitmap(left_light, LEFT_X, LEFT_Y, 0);
        al_draw_bitmap(right_light, RIGHT_X, RIGHT_Y, 0);
        al_draw_bitmap(top_light, TOP_X, TOP_Y, 0);
        al_draw_bitmap(bottom_light, BOTTOM_X, BOTTOM_Y, 0);
        al_flip_display();
        al_rest(0.1);
        al_draw_bitmap(simon_background, 0, 0, 0);
        al_flip_display();
        al_rest(0.1);
    }
}

void correct_sequence ( void )
{
    
}