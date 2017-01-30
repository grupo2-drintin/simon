#include "al_display_management.h"

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
    else if( !(event_queue = al_create_event_queue()) )
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
        return -1;
    }   
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_draw_bitmap(simon_background, 0, 0, 0);
    al_flip_display();
//    al_register_event_source(event_queue, al_get_mouse_event_source());
}

int get_event (void)
{
    int event_code;                         //0 escape, 1 a 4 botones del simon
    al_wait_for_event(event_queue, &ev);
    if (ev.type == ALLEGRO_EVENT_KEY_UP)
        
    /* los codigos de allegro para las teclas izq, der, arriba y abajo
     * son entero sucesivos en ese mismo orden
     */
    {
        if ( ev.keyboard.keycode >= ALLEGRO_KEY_LEFT  
          && ev.keyboard.keycode <= ALLEGRO_KEY_DOWN )
            
        /* al restarle ALLEGRO_KEY_LEFT, los codigos quedan:
         * tecla izq: 0
         * tecla der: 1
         * tecla arriba: 2
         * tecla abajo: 3
         */        
        {
            event_code = ev.keyboard.keycode - ALLEGRO_KEY_LEFT; 
        }
        else if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            event_code = EXIT_SIMON;
        }
    }
 //   else if (ev.type == ALLEGRO_MOUSE_EVENT)      FALTA HACER LA PARTE DEL MOUSE
    {
    
    }
    return (event_code);
}
void turn_light_on (int button) 
{
    al_draw_bitmap(simon_background, 0, 0, 0);
    switch (button)
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
        //No es necesario hacer un case para LIGHTS_OFF, ya que en ese caso no se carga
        //ningun bitmap ademas del fondo
    }
    al_flip_display();
}
void finalizacion (void)
{
    //destruir los elementos creados antes de finalizar el programa
    al_destroy_display(main_display);
    al_destroy_bitmap(simon_background);
    al_destroy_bitmap(left_light);
    al_destroy_bitmap(right_light);
    al_destroy_bitmap(top_light);
    al_destroy_bitmap(bottom_light);
    al_destroy_event_queue(event_queue);
}
