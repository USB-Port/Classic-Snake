/*
*	USB-Port.
*
*
*/
#pragma once
#ifndef SNAKE_H
#define SANKE_H

#include <allegro5\allegro.h>

class Snake
{
private:
	float  posX;
	float  posY;
	float  prevPosX;
	float  prevPosY;
	float size;
	
public:
	Snake(float  x, float  y,  Snake *leading);
	Snake(float  x, float  y);

	Snake *leadingSnake;
	float  getPosX();
	float  getPosY();

	float  getPrevPosX();
	float  getPrevPosY();

	float getSize();

	void setPosX(float  x);
	void setPosY(float  y);

	void setPrevPosX(float  x);
	void setPrevPosY(float  y);

	void drawSnake(float  x, float  y);

};


#endif