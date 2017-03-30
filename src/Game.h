#pragma once

#include "ofMain.h"

#define WIDTH 11
#define HEIGHT 19
#define SCALE 3

class Game{
	public:
		Game();

		void setup();
		void update();
		void draw();

		int ballX;
		int ballY;
		int vx;
		int vy;
		int p1X;
		int p2X;
};

