#include "al_display_management.h"

static ALLEGRO_DISPLAY *main_display = NULL;
static ALLEGRO_TIMER *fps_timer = NULL;
static ALLEGRO_BITMAP *simon_background = NULL;
static ALLEGRO_BITMAP *top_light = NULL;
static ALLEGRO_BITMAP *right_light = NULL;
static ALLEGRO_BITMAP *bottom_light = NULL;
static ALLEGRO_BITMAP *left_light = NULL;
static ALLEGRO_SAMPLE *top_beep = NULL;
static ALLEGRO_SAMPLE *right_beep = NULL;
static ALLEGRO_SAMPLE *bottom_beep = NULL;
static ALLEGRO_SAMPLE *left_beep = NULL;
static ALLEGRO_EVENT_QUEUE *event_queue = NULL;
static ALLEGRO_EVENT ev;

int inicializacion(void)
{
    if(!al_init())
    {
            fprintf(stderr, "Unable to start allegro\n");
            return -1;
    }
    else if( !al_install_keyboard()) 
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
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_draw_bitmap(simon_background, 0, 0, 0);
    al_flip_display();
        
    if(!al_install_mouse()) {
      fprintf(stderr, "failed to initialize the mouse!\n");
      return -1;
   }
       al_register_event_source(event_queue, al_get_mouse_event_source());


//    al_register_event_source(event_queue, al_get_mouse_event_source());
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
    (  ((source_of_event == SOURCE_MOUSE) && (ev.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP)) 
    || ((source_of_event == SOURCE_KB) && (ev.type != ALLEGRO_EVENT_KEY_DOWN)) );

    if (source_of_event == SOURCE_KB)
    {
        /*  los codigos de allegro para las teclas izq, der, arriba y abajo
         *  son entero sucesivos en ese mismo orden */
        if ( ev.keyboard.keycode >= ALLEGRO_KEY_LEFT  
          && ev.keyboard.keycode <= ALLEGRO_KEY_DOWN )
            
        /* al restarle ALLEGRO_KEY_LEFT, los codigos quedan:
         * tecla izq: 0
         * tecla der: 1
         * tecla arriba: 2
         * tecla abajo: 3 */       
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
//          (ev.type == ALLEGRO_MOUSE_EVENT)      FALTA HACER LA PARTE DEL MOUSE
    }
    
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
        
            fprintf(stderr,"ev.type: %d\n", ev.type);
        
        if (ev.type == ALLEGRO_EVENT_KEY_UP)
        {
            fprintf(stderr,"tomo el key up");
            source_of_events = SOURCE_KB;
        }
        else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        {
            fprintf(stderr,"tomo el mouse button up");
            source_of_events = SOURCE_MOUSE;
        }
    }
    return source_of_events;
}
