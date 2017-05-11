#pragma once

#define WIDTH 11
#define HEIGHT 19

#define P1_UP 0
#define P1_DOWN 1
#define P1_LEFT 2
#define P1_RIGHT 3
#define P1_A 4
#define P2_UP 5
#define P2_DOWN 6
#define P2_LEFT 7
#define P2_RIGHT 8
#define P2_A 9

#define BLACK_CHAR '0'
#define WHITE_CHAR '1'
#define RED_CHAR '2'
#define GREEN_CHAR '3'
#define BLUE_CHAR '4'
#define YELLOW_CHAR '5'
#define CYAN_CHAR '6'
#define PURPLE_CHAR '7'
#define ORANGE_CHAR '8'

#include "ofMain.h"

struct Position {
	int x;
	int y;
};

class Game{
	public:
		Game();
		virtual void setup();
		virtual void update();
		virtual void updateGPIO( int index, string state );

		char pixels[ WIDTH ][ HEIGHT ];
		bool start = true;

		uint64_t timeStamp;
		int delay;
		string states[ 10 ];
};
