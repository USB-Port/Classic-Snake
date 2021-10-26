/*
*	USB-Port. 
*	
*	
*/

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/timer.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

#include "Snake.h"

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

using namespace std;


const float FPS = 5.0;
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT,KEY_SPACE
};

int setup();

int snakelenght = 0;
int lastTurn = 91;
int main() {
	ALLEGRO_DISPLAY			 *display = NULL;
	ALLEGRO_DISPLAY_MODE      disp_data;
	ALLEGRO_TIMER			 *timer = NULL;
	ALLEGRO_EVENT_QUEUE	     *event_queue = NULL;

	//Data used in the game logic
	bool redraw = true;
	bool exit = false;
	

	//Used to key track of keyboard input
	bool key[5] = { false, false, false, false,false };
	

	//Verify Allegro 5 initialization ran without fault
	if (setup()) {
		fprintf(stderr, "There was an error in the setup process");
		return -1;
	}

	//Create the timer (FPS = 60)
	timer = al_create_timer(1.0 / FPS);

	//Verify that the timer was created without fault
	if (!timer) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create a timer!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	//Create the event queue
	event_queue = al_create_event_queue();

	//Verify that the event queue was created without fault
	if (!event_queue) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create a event_queue!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return -1;
	}

	//Get the display information for the current PC
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	//Set the display to Windowed mode
	al_set_new_display_flags(ALLEGRO_WINDOWED);

	//Create the display															
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT); //This is used for testing
															  //display = al_create_display(disp_data.width, disp_data.height); //This is used for resolution independent

															  //Verify that the display was created without fault
	if (!display) {
		al_show_native_message_box(display, "Error", "Error", "Failed to create a display!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(display);
		al_destroy_timer(timer);
		al_destroy_event_queue(event_queue);
		return -1;
	}

	//Register events to the event queue
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0, 255, 0));
	al_flip_display();

	//Start the timer
	al_start_timer(timer);

	std::vector<Snake> snakes;
	Snake head(240, 240);
	snakes.push_back(head);

	//Start of the game loop
	while (!exit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			// updating game logic goes here

			//Game logic for key commands
			if (key[KEY_UP]) {
					snakes[0].setPrevPosY(snakes[0].getPosY());
					snakes[0].setPrevPosX(snakes[0].getPosX());
					snakes[0].setPosY(snakes[0].getPosY() - snakes[0].getSize());
			}

			else if (key[KEY_DOWN]) {

					snakes[0].setPrevPosY(snakes[0].getPosY());
					snakes[0].setPrevPosX(snakes[0].getPosX());
					snakes[0].setPosY(snakes[0].getPosY() + snakes[0].getSize());		
			}
			else if (key[KEY_RIGHT]) {
					snakes[0].setPrevPosY(snakes[0].getPosY());
					snakes[0].setPrevPosX(snakes[0].getPosX());
					snakes[0].setPosX(snakes[0].getPosX() + snakes[0].getSize());
			}
			else if (key[KEY_LEFT]) {
					snakes[0].setPrevPosY(snakes[0].getPosY());
					snakes[0].setPrevPosX(snakes[0].getPosX());
					snakes[0].setPosX(snakes[0].getPosX() - snakes[0].getSize());
			}
			for (int i = 1; i <= snakelenght; i++) {

				snakes[i].setPrevPosY(snakes[i].getPosY());
				snakes[i].setPrevPosX(snakes[i].getPosX());
				snakes[i].setPosY(snakes[i - 1].getPrevPosY());
				snakes[i].setPosX(snakes[i - 1].getPrevPosX());

			}
			if (key[KEY_SPACE]) {
				snakelenght++;
				if (key[KEY_UP]) {
					snakes.push_back(Snake(snakes[snakelenght-1].getPrevPosX(), snakes[snakelenght-1].getPrevPosY(), &snakes[0]));
				}
				else if (key[KEY_DOWN]) {
					snakes.push_back(Snake(snakes[snakelenght - 1].getPrevPosX(), snakes[snakelenght - 1].getPrevPosY(),  &snakes[snakelenght - 1]));
				}
				else if (key[KEY_RIGHT]) {
					snakes.push_back(Snake(snakes[snakelenght - 1].getPrevPosX(), snakes[snakelenght - 1].getPrevPosY(),  &snakes[snakelenght - 1]));
				}
				else if (key[KEY_LEFT]) {
					snakes.push_back(Snake(snakes[snakelenght - 1].getPrevPosX(), snakes[snakelenght - 1].getPrevPosY(),  &snakes[snakelenght - 1]));
				}
			}

		


			redraw = true;
		}//Timer if statement

		 //Close the program is the programed is X'ed out
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		//Check for key down input
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					key[KEY_DOWN] = false;
					key[KEY_RIGHT] = false;
					key[KEY_LEFT] = false;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					key[KEY_UP] = false;
					key[KEY_RIGHT] = false;
					key[KEY_LEFT] = false;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					key[KEY_DOWN] = false;
					key[KEY_UP] = false;
					key[KEY_LEFT] = false;
					break;

				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = true;
					key[KEY_DOWN] = false;
					key[KEY_RIGHT] = false;
					key[KEY_UP] = false;
					break;

				case ALLEGRO_KEY_SPACE:
					key[KEY_SPACE] = true;
					break;

			}
		}
		
		//Check for key up input
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					//key[KEY_UP] = false;
					break;

				case ALLEGRO_KEY_DOWN:
					//key[KEY_DOWN] = false;
					break;

				case ALLEGRO_KEY_RIGHT:
					//key[KEY_RIGHT] = false;
					break;

				case ALLEGRO_KEY_LEFT:
					//key[KEY_LEFT] = false;
					break;
				case ALLEGRO_KEY_SPACE:
					key[KEY_SPACE] = false;
					break;



				case ALLEGRO_KEY_ESCAPE:
					exit = true;
					break;
				}
		}
		

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));

			//Draw here
		
			for (int i = 0; i <= snakelenght; i++) {
				snakes[i].drawSnake(snakes[i].getPosX(), snakes[i].getPosY());
			}
			al_flip_display();
		}

	} //End of game loop

}



//This function starts many of the Allegro 5 features.
int setup() {
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_init_image_addon()) {
		fprintf(stderr, "failed to image addon!\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}

	if (!al_install_audio()) {
		fprintf(stderr, "failed to install audio!\n");
		return -1;
	}

	if (!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize acodec addon!\n");
		return -1;
	}

	if (!al_reserve_samples(1)) {
		fprintf(stderr, "failed to reserve sample!\n");
		return -1;
	}

	if (!al_init_font_addon()) {
		fprintf(stderr, "failed to initialize font addon!\n");
		return -1;
	}

	if (!al_init_ttf_addon()) {
		fprintf(stderr, "failed to initialize true text format addon!\n");
		return -1;
	}
	if (!al_init_primitives_addon()) {
		fprintf(stderr, "failed to initialize primitive  addon!\n");
		return -1;
	}

	return 0;
}
