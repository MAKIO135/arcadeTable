#pragma once

#include "ofMain.h"

#define WIDTH 11
#define HEIGHT 19

class Game{
	public:
		Game();
		void setup();
		void update();

		ofPixels pixels;
		bool start = true;

	private:
		void reset( int dir );
		void updatePixels();

		ofColor white;

		int ballX;
		int ballY;
		int vx;
		int vy;
		bool bouncing;

		int p1X;
		int p2X;
};
