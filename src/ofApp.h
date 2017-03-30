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
		void updateFbo();
		void getPixels();
		void serialize();

		ofFbo fbo;
		ofPixels fboPixels;
		//ofImage img;

		ofSerial serial;
		bool a[ 19 ][ 11 ];
		unsigned char buf[ 210 ];

		Game game;
};
