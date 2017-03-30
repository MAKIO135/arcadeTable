#include "Game.h"

Game::Game(){
}

void Game::setup() {
	pixels.allocate( WIDTH, HEIGHT, OF_PIXELS_RGB );
	white.r = 255;
	white.g = 255;
	white.b = 255;

	ballX = WIDTH / 2;
	ballY = HEIGHT / 2;
	vx = 1;
	vy = 1;
	p1X = WIDTH / 2;
	p2X = WIDTH / 2;
}

void Game::update(){
	p1X = int( ofGetMouseX() / 20 );
	p2X = int( ofGetMouseX() / 20 );
	p1X = ofClamp( p1X, 1, WIDTH - 2 );
	p2X = ofClamp( p2X, 1, WIDTH - 2 );

	ballX += vx;
	ballY += vy;

	/*
	//before Collisions
	if ( ballY == 2 ) {
		if ( ballX + vx >= p1X - 1 && ballX + vx <= p1X + 1 ) {
			vy = -vy;
			if ( ballX + vx == p1X - 1 ) vx = -1;
			else if ( ballX + vx == p1X ) vx = 0;
			else vx = 1;
		}
	}

	if ( ballY == HEIGHT - 3 ){
		if ( ballX + vx >= p2X - 1 && ballX + vx <= p2X + 1 ) {
			vy = -vy;
			if ( ballX + vx == p2X - 1 ) vx = -1;
			else if ( ballX + vx == p2X ) vx = 0;
			else vx = 1;
		}
	}
	*/

	// world collisions
	if ( ballX < 0 || ballX > WIDTH - 1 ) {
		ofClamp( ballX, 1, WIDTH - 2 );
		vx = -vx;
	}

	if ( ballY < 0 || ballY > HEIGHT - 1 ) {
		ofClamp( ballY, 1, HEIGHT - 2 );
		vy = -vy;
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