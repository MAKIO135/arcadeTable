#pragma once

#include "ofMain.h"
#include "Game.h"

#define WIDTH 11
#define HEIGHT 19

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void getPixels();
		void serialize();
		
		ofSerial serial;
		unsigned char buf[ 210 ];

		Game game;
};
