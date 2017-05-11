#pragma once

#include "ofMain.h"
#include "Game.h"

class Snake : public Game{
	public:
		Snake();
		virtual void setup();
		virtual void update();
		virtual void updateGPIO( int index, string state );

	private:
		void reset();
		void updatePixels();

		Position placeFood();
		bool isInSnake( Position & p );

		vector<Position> snake;
		Position food;
		bool vitChanged = true;
		int vx, vy;
};
