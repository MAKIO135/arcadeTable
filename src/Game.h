#pragma once

#include "ofMain.h"

#define WIDTH 11
#define HEIGHT 19
class Game{
	public:
		Game();

		void setup();
		void update();
		void updatePixels();

		ofPixels pixels;
		ofColor white;

		int ballX;
		int ballY;
		int vx;
		int vy;
		int p1X;
		int p2X;
};