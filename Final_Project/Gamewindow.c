#include "GameWindow.h"
//static ALLEGRO_DISPLAY *screen; fox
static char const *filename;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_EVENT event;
//ALLEGRO_TIMER *timer; fox
ALLEGRO_VIDEO *video;
//fox
bool draw = false;

const char* title = "LegendKnight";

// ALLEGRO Variables
ALLEGRO_DISPLAY* display = NULL;
ALLEGRO_SAMPLE* song = NULL;
ALLEGRO_SAMPLE_INSTANCE* sample_instance;

int Game_establish() {
    int msg = 0;

    game_init();
    game_begin();

    while (msg != GAME_TERMINATE) {
        msg = game_run();
        if (msg == GAME_TERMINATE)
            printf("Game Over\n");
    }

    game_destroy();
    return 0;
}

void game_init() {
    printf("Game Initializing...\n");
    al_init();
    // init audio
    al_install_audio();
    al_init_acodec_addon();
    // Create display
    display = al_create_display(WIDTH, HEIGHT);
    // create event queue
    event_queue = al_create_event_queue();
    // Initialize Allegro settings
    al_set_window_position(display, 0, 0);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon
    al_init_video_addon();//fox
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event
    // Register event
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    fps = al_create_timer(1.0 / FPS);
    al_register_event_source(event_queue, al_get_timer_event_source(fps));
    // initialize the icon on the display
    ALLEGRO_BITMAP* icon = al_load_bitmap("./image/icon.jpg");
    al_set_display_icon(display, icon);
    //fox
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    /*filename = "./video/Overdrive+_+PROJECT+Animated+Trailer+-+League+of+Legends_out.ogv";
    printf("reading video.....\n");
    video = al_open_video(filename);
    if( video )
        printf("read video succeed\n");
    else
        printf("read video fail!!!!\n");
    queue = al_create_event_queue();
    // register video event
    ALLEGRO_EVENT_SOURCE *temp = al_get_video_event_source(video);
    al_register_event_source(queue, temp);
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(fps));*/
    //fox
}


void game_begin() {
    //fox
    /*filename = "./video/Overdrive+_+PROJECT+Animated+Trailer+-+League+of+Legends_out.ogv";
    printf("reading video.....\n");
    video = al_open_video(filename);
    if( video )
        printf("read video succeed\n");
    else
        printf("read video fail!!!!\n");
    queue = al_create_event_queue();
    // register video event
    ALLEGRO_EVENT_SOURCE *temp = al_get_video_event_source(video);
    al_register_event_source(queue, temp);
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(fps));
    video_begin();
    while( 1 ){
        al_wait_for_event(queue, &event);
        if( event.type == ALLEGRO_EVENT_TIMER ) {
            video_display(video);
        } else if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
            al_close_video(video);
            break;
        } else if( event.type == ALLEGRO_EVENT_VIDEO_FINISHED ) {
            break;
        }
    }*/
    //destroy_video();
    //fox
    // Load sound
    song = al_load_sample("./sound/KDA - POPSTARS.mp3");
    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(sample_instance, 2);
    al_play_sample_instance(sample_instance);
    al_start_timer(fps);
    // initialize the menu before entering the loop
    window = MENU;
    button_effect_init();
    menu_init();

}
void game_update() {
    if (window == MENU) {
        if(judge_next_window == GAME) window = PROCESS;
        if(judge_next_window == CHARATER) {
            character_scene_init();
            window = CHARACTER;
        }
        judge_next_window = DEFAULT;
    }

    if(window == CHARATER) {
        if (judge_next_window == MENU) {
            character_scene_destroy();
            window = MENU;
        }
        judge_next_window = DEFAULT;
    }

    if (window == PROCESS) {
        game_scene_init();
        judge_next_window = DEFAULT;
        window = GAME;
    }

    if (window == GAME) {
        charater_update();
        if (judge_next_window == PAUSE) {
            pause_scene_init();
            window = PAUSE;
        }
        judge_next_window = false;
    }

    if (window == PAUSE) {
        if (judge_next_window == GAME) {
            pause_scene_destroy();
            window = GAME;
        }
        if (judge_next_window == MENU) {
            game_scene_destroy();
            pause_scene_destroy();
            window = MENU;
        }
        judge_next_window = DEFAULT;
    }
}
int process_event() {
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);
    button_effect_update(event);
    // process the event of other component
    if (window == MENU) {
        menu_process(event);
    }
    else if (window == GAME) {
        charater_process(event);
        game_process(event);
    }
    else if (window == PAUSE) {
        pause_process(event);
    }

    // Shutdown our program
    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;
    else if (event.type == ALLEGRO_EVENT_TIMER)
        if (event.timer.source == fps)  draw = true;

    return 0;
}
void game_draw() {
    if (window == MENU) {
        menu_draw();
    }
    else if (window == CHARACTER){
        character_scene_draw();
    }
    else if (window == GAME) {
        game_scene_draw();
        charater_state_update();
    }
    else if (window == PAUSE) {
        pause_scene_draw();
    }
    al_flip_display();
}
int game_run() {
    int error = 0;
    if (draw) {
        game_draw();
        game_update();
        draw = false;
    }
    if (!al_is_event_queue_empty(event_queue)) {
        error = process_event();
    }
    return error;
}

void game_destroy() {
    // Make sure you destroy all things
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    game_scene_destroy();
    pause_scene_destroy();
    button_effect_destroy();
    object_free();
}
//fox
/*static ALLEGRO_DISPLAY *screen;
static char const *filename;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *timer;
ALLEGRO_VIDEO *video;*/
/*void video_display(ALLEGRO_VIDEO *video) {
    ALLEGRO_BITMAP *frame = al_get_video_frame(video);
    // check if we get the frame successfully
    // Note the this code is necessary
    if ( !frame )
        return;
    // Display the frame.
    // rescale the frame into the size of screen
    al_draw_scaled_bitmap(frame,
                          // the rescale position of the frame
                          0, 0,
                          // the width and height you want to rescale
                          al_get_bitmap_width(frame),
                          al_get_bitmap_height(frame),
                          // the position of result image
                          0, 0,
                          // the width and height of result image
                          al_get_display_width(display),//fox
                          al_get_display_height(display), 0);//fox screen-display
    al_flip_display();
}*/

/*void init_video(){
    al_init();
    al_init_video_addon();
    al_install_audio();
    timer = al_create_timer(1.0 / 60);
    //al_set_new_display_flags(ALLEGRO_RESIZABLE);
    //al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    screen = al_create_display(1366, 784);
    // linear interpolation for scaling images
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    filename = "./video/Overdrive+_+PROJECT+Animated+Trailer+-+League+of+Legends_out.ogv";
    printf("reading video.....\n");
    video = al_open_video(filename);
    if( video )
        printf("read video succeed\n");
    else
        printf("read video fail!!!!\n");
    queue = al_create_event_queue();
    // register video event
    ALLEGRO_EVENT_SOURCE *temp = al_get_video_event_source(video);
    al_register_event_source(queue, temp);
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(fps));

}*/
//mai.c
void video_begin(){
    al_reserve_samples(1);
    al_start_video(video, al_get_default_mixer());
    al_start_timer(fps);
}
/*void destroy_video(){
    al_destroy_display(display);
    al_destroy_event_queue(queue);
}*/


