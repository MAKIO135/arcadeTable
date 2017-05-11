#pragma once

#include "ofMain.h"
#include "Game.h"

class Tron : public Game {
	public:
		Tron();
		virtual void setup();
		virtual void update();
		virtual void updateGPIO( int index, string state );

	private:
		void reset();
		void updatePixels();

		Position placeFood();
		Position food;

		vector<Position> snake;
		bool isInSnake( Position & p );
		bool vitChanged = true;
		int vx, vy;

		vector<Position> snake2;
		bool isInSnake2( Position & p );
		bool vitChanged2 = true;
		int vx2, vy2;
};
