#include "Game.h"

Game::Game(){
}

void Game::setup() {
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

	//player Collisions
	/*
	if ( ballY == 1 ) {
		if ( ballX >= p1X - 1 && ballX <= p1X + 1 ) {
			ballY = 3;
			vy = -vy;
			if ( ballX == p1X - 1 ) vx = -1;
			else if ( ballX == p1X ) vx = 0;
			else vx = 1;
		}
	}
	if ( ballY == HEIGHT - 2 ){
		if ( ballX >= p2X - 1 && ballX <= p2X + 1 ) {
			ballY = HEIGHT - 3;
			vy = -vy;
			if ( ballX == p2X - 1 ) vx = -1;
			else if ( ballX == p2X ) vx = 0;
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
}

void Game::draw(){
	ofBackground( 0 );
	ofSetColor( 255 );
	ofFill();
	ofDrawRectangle( ballX, ballY, 0, 1 );

	ofDrawRectangle( p1X - 1, 1, 3, 1 );
	ofDrawRectangle( p2X - 1, HEIGHT - 2, 3, 1 );
}
