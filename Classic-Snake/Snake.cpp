/*
*	USB-Port.
*
*
*/
#include "Snake.h"
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>
#include <iostream>

using namespace std;
	

	Snake::Snake(float  x, float  y, Snake *leading) {
		posX = x;
		posY = y;
		size = 25;
		leadingSnake = leading;
		
	}
	Snake::Snake(float  x, float  y) {
		posX = x;
		posY = y;
		size = 25;
		leadingSnake = NULL;
		
	}
	float  Snake::getPosX() {
		return posX;
	}
	float  Snake::getPosY() {
		return posY;
	}

	float Snake::getSize() {
		return size;
	}

	void Snake::setPosX(float  x) {
		posX = x;
	}
	void Snake::setPosY(float  y) {
		posY = y;
	}

	float Snake::getPrevPosX() {
		return prevPosX;
	}
	float  Snake::getPrevPosY() {
		return prevPosY;
	}
	void Snake::setPrevPosX(float  x) {
		prevPosX = x;
	}
	void Snake::setPrevPosY(float  y) {
		prevPosY = y;
	}

	void Snake::drawSnake(float  x, float  y) {
		al_draw_filled_rectangle(posX, posY, posX + size, posY + size, al_map_rgb(0, 255, 0));
		//cout << "Snake X: " << posX<< "Snake Y: " << posY << endl;

	}
