#pragma once

#include "ofMain.h"
#include "Game.h"

#define SERIAL false

#define WIDTH 11
#define HEIGHT 19

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		Game game;

#if SERIAL
		void serialize();
		ofSerial serial;
		unsigned char buf[ 210 ];
#endif
};
