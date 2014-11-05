#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "tetrismap.h"
#include "timer.h"


const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;
const int sprites_size = 15;
const int cells_space = 2;
const int ROWS=20;
const int COLS=10;
const unsigned int MAPSIZEX=COLS;
using namespace std;
vector<ALLEGRO_BITMAP *> sprites(TTRsize,0);
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};
void draw_map(const tetrismap & map){
   al_clear_to_color(al_map_rgb(0, 0, 0));
   for(unsigned int i=0;i<map.rowsize();i++){
      for(unsigned int j=0; j<map.colsize();j++){
         if(map(i,j)!=TTRsize)
            al_draw_bitmap(sprites[map(i,j)],j*sprites_size+j*cells_space,i*sprites_size+i*cells_space,0);
      }
   }
   al_flip_display();
}
void uinttostring(unsigned int n, char * s){
   for(int i=strlen(s)-1;i>-1;i--){
      s[i]=n%10+'0';
      n/=10;
   }
}
int main(int argc, char **argv)
{
   char * score=new char[7];
   for(int i=0; i<6;i++)
      score[i]='0';
   score[6]=0;
   cout<<log10(123413)+1;
   
   srand(time(NULL));
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_SAMPLE *sample=NULL;
   ALLEGRO_BITMAP *bouncer = NULL;
   ALLEGRO_BITMAP *bitmapLZ = NULL ,*bitmapITO = NULL,*bitmapJS = NULL;
   tetrismap map(20,10,true);
   float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
   float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
   vector<bool>ttrkey(ACT_SIZE,false);
   bool key[4] = { false, false, false, false };
   bool redraw = true;
   bool doexit = false;
 
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_image_addon();
       
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
 
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }
   if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
   }
   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
   }
   sample = al_load_sample( "/Users/Pablo/Documents/Programacion/C++/Proyectoallegro/Tetris/datos/SneakySnitch.wav" );
 
   if (!sample){
      printf( "Audio clip sample not loaded!\n" ); 
      return -1;
   }
   bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
   if(!bouncer) {
      fprintf(stderr, "failed to create bouncer bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
   bitmapITO = al_load_bitmap("/Users/Pablo/Documents/Programacion/C++/Proyectoallegro/Tetris/datos/bitmapprueba.png");
   if(!bitmapITO) {
      fprintf(stderr, "failed to load bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      al_destroy_bitmap(bouncer);
      return -1;
   }
   bitmapITO = al_load_bitmap("/Users/Pablo/Documents/Programacion/C++/Proyectoallegro/Tetris/datos/bitmapITO.png");
   if(!bitmapITO) {
      fprintf(stderr, "failed to load bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      al_destroy_bitmap(bouncer);
      return -1;
   }
   bitmapJS = al_load_bitmap("/Users/Pablo/Documents/Programacion/C++/Proyectoallegro/Tetris/datos/bitmapJS.png");
   if(!bitmapJS) {
      fprintf(stderr, "failed to load bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      al_destroy_bitmap(bouncer);
      al_destroy_bitmap(bitmapITO);
      return -1;
   }
   bitmapLZ = al_load_bitmap("/Users/Pablo/Documents/Programacion/C++/Proyectoallegro/Tetris/datos/bitmapLZ.png");
   if(!bitmapJS) {
      fprintf(stderr, "failed to load bitmap!\n");
      al_destroy_display(display);
      al_destroy_timer(timer);
      al_destroy_bitmap(bouncer);
      al_destroy_bitmap(bitmapITO);
      al_destroy_bitmap(bitmapJS);
      return -1;
   }
   al_init_font_addon(); // initialize the font addon
   al_init_ttf_addon();
   sprites=vector<ALLEGRO_BITMAP *>(TTRsize);
   sprites[TTRT]=sprites[TTRI]=sprites[TTRO]=bitmapITO;
   sprites[TTRS]=sprites[TTRJ]=bitmapJS;

   sprites[TTRL]=sprites[TTRZ]=bitmapLZ;
 
   al_clear_to_color(al_map_rgb(255, 255, 0));

   al_set_target_bitmap(al_get_backbuffer(display));
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      fprintf(stderr, "failed to create event_queue!\n");
      al_destroy_bitmap(bouncer);
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
    ALLEGRO_FONT *font = al_load_ttf_font("/Users/Pablo/Documents/Programacion/C++/Proyectoallegro/Tetris/datos/PressStart2P.ttf",30,0 );
 
   if (!font){
      fprintf(stderr, "Could not load 'pirulen.ttf'.\n");
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
 
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
 
   al_register_event_source(event_queue, al_get_keyboard_event_source());
 
   al_clear_to_color(al_map_rgb(255,255,0));

   al_start_timer(timer);

   //¡¡QUE EMPIEZE LA FIESTA!!
    bool act_nothing;
    al_play_sample(sample, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
    map.start();
    while(!doexit&& map.getactive())
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER/*?*/) {
          act_nothing=true;
          for(int i=0; i<ACT_SIZE;i++){
            if(ttrkey[i]){
              map.sendaction(inttoaction(i));
              act_nothing=false;
            }
          }
          if(act_nothing){
            map.sendaction(ACT_SIZE);
          }
 
         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_DOWN:
            case ALLEGRO_KEY_S:
               ttrkey[ACT_DOWN] = true;
               break;
 
            case ALLEGRO_KEY_LEFT:
            case ALLEGRO_KEY_A: 
               ttrkey[ACT_LEFT] = true;
               break;
 
            case ALLEGRO_KEY_RIGHT:
            case ALLEGRO_KEY_D: 
               ttrkey[ACT_RIGHT] = true;
               break;
         
            case ALLEGRO_KEY_K:
            case ALLEGRO_KEY_Z: 
               ttrkey[ACT_CCW] = true;
               break;
            case ALLEGRO_KEY_L:
            case ALLEGRO_KEY_X: 
               ttrkey[ACT_CW] = true;
               break;
            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;
         }

      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_DOWN:
            case ALLEGRO_KEY_S:
               ttrkey[ACT_DOWN] = false;
               break;
 
            case ALLEGRO_KEY_LEFT:
            case ALLEGRO_KEY_A: 
               ttrkey[ACT_LEFT] = false;
               break;
 
            case ALLEGRO_KEY_RIGHT:
            case ALLEGRO_KEY_D: 
               ttrkey[ACT_RIGHT] = false;
               break;
         
            case ALLEGRO_KEY_K:
            case ALLEGRO_KEY_Z: 
               ttrkey[ACT_CCW] = false;
               break;
            case ALLEGRO_KEY_L:
            case ALLEGRO_KEY_X: 
               ttrkey[ACT_CW] = false;
               break;
         }
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
 
         draw_map(map);
      }
   }
   al_clear_to_color(al_map_rgb(50,10,70));
   uinttostring(map.getscore(),score);
   al_draw_text(font, al_map_rgb(255,255,255), 640/2, (480/4),ALLEGRO_ALIGN_CENTRE,score);
   al_flip_display();
   al_rest(10.0);
   al_destroy_bitmap(bouncer);
   al_destroy_bitmap(bitmapITO);
   al_destroy_bitmap(bitmapJS);
   al_destroy_bitmap(bitmapLZ);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}