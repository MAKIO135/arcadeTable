#include "Pong.h"

Pong::Pong(){
}

void Pong::setup() {
	ofLog() << "Pong setup";
	reset( 1 );
}

void Pong::reset( int dir ) {
	for ( int i = 0; i < 10; i++ ) {
		Game::states[ i ] = "";
	}

	Game::timeStamp = -1000;
	Game::delay = 100;
	Game::start = true;

	ballX = WIDTH / 2;
	ballY = HEIGHT / 2;
	vx = 0;
	vy = dir;
	bouncing = false;

	p1X = WIDTH / 2;
	p2X = WIDTH / 2;
}

void Pong::movePlayer( int id, int dir ) {
	if ( id == 0 ) {
		p1X += dir;
	}
	else {
		p2X += dir;
	}

	p1X = ofClamp( p1X, 1, WIDTH - 2 );
	p2X = ofClamp( p2X, 1, WIDTH - 2 );
}

void Pong::update(){
	if ( ofGetElapsedTimeMillis() - Game::timeStamp > Game::delay ) {
		Game::timeStamp = ofGetElapsedTimeMillis();

		if ( ballY == HEIGHT / 2 ) bouncing = false;

		// players Collisions
		bool isBouncing = false;
		if ( ballY == 2 && !bouncing ) {
			if ( ballX == p2X - 1 ) {
				vx = -1;
				isBouncing = true;
			}
			else if ( ballX == p2X ) {
				vx = 0;
				isBouncing = true;
			}
			else if ( ballX == p2X + 1 ) {
				vx = 1;
				isBouncing = true;
			}
			else if ( ballX + vx == p2X - 1 ) {
				vx = -1;
				isBouncing = true;
			}
			else if ( ballX + vx == p2X + 1 ) {
				vx = 1;
				isBouncing = true;
			}
		}
		else if( ballY == 1 ) {
			if ( ballX == p2X - 1 ) {
				vx = -1;
				isBouncing = true;
			}
			else if ( ballX == p2X ) {
				vx = 0;
				isBouncing = true;
			}
			else if ( ballX == p2X + 1 ) {
				vx = 1;
				isBouncing = true;
			}
		}
		else if ( ballY == HEIGHT - 3 && !bouncing ){
			if ( ballX == p1X - 1 ) {
				vx = -1;
				isBouncing = true;
			}
			else if ( ballX == p1X ) {
				vx = 0;
				isBouncing = true;
			}
			else if ( ballX == p1X + 1 ) {
				vx = 1;
				isBouncing = true;
			}
			else if ( ballX + vx == p1X - 1 ) {
				vx = -1;
				isBouncing = true;
			}
			else if ( ballX + vx == p1X + 1 ) {
				vx = 1;
				isBouncing = true;
			}
		}
		else if ( ballY == HEIGHT - 2) {
			if ( ballX == p1X - 1 ) {
				vx = -1;
				isBouncing = true;
			}
			else if ( ballX == p1X ) {
				vx = 0;
				isBouncing = true;
			}
			else if ( ballX == p1X + 1 ) {
				vx = 1;
				isBouncing = true;
			}
		}

		if( isBouncing ){
			vy = -vy;
			bouncing = true;
			Game::delay -= 5;
			Game::delay  = ofClamp( Game::delay, 5, 100 );
		}

		ballX += vx;
		ballY += vy;

		// world collisions
		if ( ballX < 0 || ballX > WIDTH - 1 ) {
			ballX = ofClamp( ballX, 1, WIDTH - 2 );
			vx = -vx;
		}

		// score!
		if ( ballY < 0 || ballY > HEIGHT - 1 ) {
			// ballY = ofClamp( ballY, 1, HEIGHT - 2 );
			ofSleepMillis( 1000 );

			if ( ballY < 0 ) reset( 1 );
			else reset( -1 );
		}
	}

	updatePixels();
}

void Pong::updateGPIO( int index, string state ) {
	//if ( states[ index ] != state ) {
	Game::states[ index ] = state;

	if ( Game::states[ index ] == "1" ) {
		switch ( index ) {
			case P1_UP:
				break;
			case P1_DOWN:
				break;
			case P1_LEFT:
				movePlayer( 0, -1 );
				break;
			case P1_RIGHT:
				movePlayer( 0, 1 );
				break;
			case P1_A:
				break;
			case P2_UP:
				break;
			case P2_DOWN:
				break;
			case P2_LEFT:
				movePlayer( 1, 1 );
				break;
			case P2_RIGHT:
				movePlayer( 1, -1 );
				break;
			case P2_A:
				break;
			default:
				break;
		}
	}
	//}
}

void Pong::updatePixels(){
	for ( int i = 0; i < WIDTH; i++ ) {
		for ( int j = 0; j < HEIGHT; j++ ) {
			Game::pixels[ i ][ j ] = BLACK_CHAR;
		}
	}

	// draw Ball
	Game::pixels[ ballX ][ ballY ] = CYAN_CHAR;

	// draw P1
	for ( int x = p1X - 1; x < p1X + 2; x++ ) {
		Game::pixels[ x ][ HEIGHT - 2 ] = WHITE_CHAR;
	}

	// draw P2
	for ( int x = p2X - 1; x < p2X + 2; x++ ) {
		Game::pixels[ x ][ 1 ] = WHITE_CHAR;
	}
}
