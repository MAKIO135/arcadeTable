#pragma once

//#define USE_RENDER
#define USE_SERIAL
#define USE_GPIO

#define GPIO_P1_UP "23"
#define GPIO_P1_DOWN "24"
#define GPIO_P1_LEFT "10"
#define GPIO_P1_RIGHT "9"
#define GPIO_P1_A "11"

#define GPIO_P2_UP "4"
#define GPIO_P2_DOWN "17"
#define GPIO_P2_LEFT "18"
#define GPIO_P2_RIGHT "27"
#define GPIO_P2_A "22"

#define WIDTH 11
#define HEIGHT 19

#define FRAMERATE 20
#define NB_GAMES 4

#include "ofMain.h"
#include "Game.h"
#include "Pong.h"
#include "Snake.h"
#include "Tron.h"
#include "Tetris.h"
#ifdef USE_GPIO
#include "ofxGPIO.h"
#endif

class ofApp : public ofBaseApp{
	public:
		void setup();
		void initGame();
		void update();
		void draw();

#ifdef USE_RENDER
		void keyPressed( int key );
		void keyReleased( int key );
#endif

		Game *game;
		int gameSelection = 0;

#ifdef USE_SERIAL
		void serialize();
		ofSerial serial;
		unsigned char buf[ 210 ];
#endif

#ifdef USE_GPIO
		GPIO gpios[ 10 ];
#endif
};
