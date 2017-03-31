#include "Game.h"

Game::Game(){
}

void Game::setup() {
	pixels.allocate( WIDTH, HEIGHT, OF_PIXELS_RGB );
	white.r = 255;
	white.g = 255;
	white.b = 255;

	reset( 1 );
}

void Game::reset( int dir ) {
	start = true;

	ballX = WIDTH / 2;
	ballY = HEIGHT / 2;
	vx = 0;
	vy = dir;
	bouncing = false;

	p1X = WIDTH / 2;
	p2X = WIDTH / 2;
}

void Game::update(){
	if ( ballY == HEIGHT / 2 ) bouncing = false;

	// players Collisions
	if ( ballY == 2 && !bouncing ) {
		if ( ballX == p1X - 1 ) {
			vx = -1;
			vy = -vy;
			bouncing = true;
		}
		else if ( ballX == p1X ) {
			vx = 0;
			vy = -vy;
			bouncing = true;
		}
		else if ( ballX == p1X + 1 ) {
			vx = 1;
			vy = -vy;
			bouncing = true;
		}
		else if ( ballX + vx == p1X - 1 ) {
			vx = -1;
			vy = -vy;
			bouncing = true;
		}
		else if ( ballX + vx == p1X + 1 ) {
			vx = 1;
			vy = -vy;
			bouncing = true;
		}
	}
	else if( ballY == 1 ) {
		if ( ballX == p1X - 1 ) {
			vx = -1;
			vy = -vy;
			bouncing = true;
		}
		else if ( ballX == p1X ) {
			vx = 0;
			vy = -vy;
			bouncing = true;
		}
		else if ( ballX == p1X + 1 ) {
			vx = 1;
			vy = -vy;
			bouncing = true;
		}
	}
	else if ( ballY == HEIGHT - 3 && !bouncing ){
		if ( ballX == p2X - 1 ) {
			vx = -1;
			vy = -vy;
			bouncing = true;
		}
		else if ( ballX == p2X ) {
			vx = 0;
			vy = -vy;
			bouncing = true;
		}
		else if ( ballX == p2X + 1 ) {
			vx = 1;
			vy = -vy;
			bouncing = true;
		}
		else if ( ballX + vx == p2X - 1 ) {
			vx = -1;
			vy = -vy;
			bouncing = true;
		}
		else if ( ballX + vx == p2X + 1 ) {
			vx = 1;
			vy = -vy;
			bouncing = true;
		}
	}
	else if ( ballY == HEIGHT - 2) {
		if ( ballX == p2X - 1 ) {
			vx = -1;
			vy = -vy;
			bouncing = true;
		}
		else if ( ballX == p2X ) {
			vx = 0;
			vy = -vy;
			bouncing = true;
		}
		else if ( ballX == p2X + 1 ) {
			vx = 1;
			vy = -vy;
			bouncing = true;
		}
	}


	// update positions
	p1X = int( ofGetMouseX() / 20 );
	p2X = int( ofGetMouseX() / 20 );
	p1X = ofClamp( p1X, 1, WIDTH - 2 );
	p2X = ofClamp( p2X, 1, WIDTH - 2 );

	ballX += vx;
	ballY += vy;


	// world collisions
	if ( ballX < 0 || ballX > WIDTH - 1 ) {
		ballX = ofClamp( ballX, 1, WIDTH - 2 );
		vx = -vx;
	}

	if ( ballY < 0 || ballY > HEIGHT - 1 ) {
		ballY = ofClamp( ballY, 1, HEIGHT - 2 );
		ofSleepMillis( 1000 );

		if ( ballY == 1 ) reset( 1 );
		else reset( -1 );
	}

	updatePixels();
}

void Game::updatePixels(){
	pixels.setColor( ofColor( 0, 0, 0 ) );

	// draw Ball
	pixels.setColor( ballX, ballY, white );

	// draw P1
	for ( int x = p1X - 1; x < p1X + 2; x++ ) {
		pixels.setColor( x, 1, white );
	}

	// draw P2
	for ( int x = p2X - 1; x < p2X + 2; x++ ) {
		pixels.setColor( x, HEIGHT - 2, white );
	}
}