#pragma once

#include "ofMain.h"
#include "Game.h"

class Pong : public Game{
	public:
		Pong();
		virtual void setup();
		virtual void update();
		virtual void updateGPIO( int index, string state );

	private:
		void reset( int dir );
		void updatePixels();

		void movePlayer( int id, int dir );

		int ballX;
		int ballY;
		int vx;
		int vy;
		bool bouncing;

		int p1X;
		int p2X;
};
