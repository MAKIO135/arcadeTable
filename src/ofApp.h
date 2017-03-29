#pragma once

#include "ofMain.h"

#define SCALE 20

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void updateFbo();
		void getPixels();
		void serialize();
		void mousePressed( int x, int y, int button );

		ofFbo fbo;
		ofPixels fboPixels;
		ofImage img;

		ofSerial serial;
		bool a[ 19 ][ 11 ];
		unsigned char buf[ 210 ];
		bool play;
};
