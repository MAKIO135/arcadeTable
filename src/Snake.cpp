#include "Snake.h"

Snake::Snake(){
}

void Snake::setup() {
	reset();
}

void Snake::reset() {
	food = placeFood();

	vx = 0;
	vy = 1;

	snake.clear();
	for ( int i = 0; i < 3; i++ ) {
		snake.push_back( { 5, 5 - i * vy } );
	}
}

void Snake::update() {
	Position first = { ( snake[ 0 ].x + vx  + WIDTH ) % WIDTH, ( snake[ 0 ].y + vy + HEIGHT ) % HEIGHT };

	if ( isInSnake( first ) ) {
		ofSleepMillis( 3000 );
		reset();
	}
	else {
		vector<Position>::iterator it = snake.begin();
		snake.insert( it, first );

		if ( snake[ 0 ].x == food.x && snake[ 0 ].y == food.y ) food = placeFood();
		else snake.pop_back();

		updatePixels();
		vitChanged = true;
	}
}

void Snake::updateGPIO( int index, string state ) {
	if ( states[ index ] != state ) {
		states[ index ] = state;

		if ( states[ index ] == "1" ) {
			switch ( index ) {
			case P1_UP:
				if ( vy != 1 ) {
					vx = 0;
					vy = -1;
					vitChanged = false;
				}
				break;
			case P1_DOWN:
				if ( vy != -1 ) {
					vx = 0;
					vy = 1;
					vitChanged = false;
				}
				break;
			case P1_LEFT:
				if ( vx != 1 ) {
					vx = -1;
					vy = 0;
					vitChanged = false;
				}
				break;
			case P1_RIGHT:
				if ( vx != -1 ) {
					vx = 1;
					vy = 0;
					vitChanged = false;
				}
				break;
			case P1_A:
				break;
			case P2_UP:
				if ( vy != -1 ) {
					vx = 0;
					vy = 1;
					vitChanged = false;
				}
				break;
			case P2_DOWN:
				if ( vy != 1 ) {
					vx = 0;
					vy = -1;
					vitChanged = false;
				}
				break;
			case P2_LEFT:
				if ( vx != -1 ) {
					vx = 1;
					vy = 0;
					vitChanged = false;
				}
				break;
			case P2_RIGHT:
				if ( vx != 1 ) {
					vx = -1;
					vy = 0;
					vitChanged = false;
				}
				break;
			case P2_A:
				break;
			default:
				break;
			}
		}
	}
}

void Snake::updatePixels(){
	for ( int i = 0; i < WIDTH; i++ ) {
		for ( int j = 0; j < HEIGHT; j++ ) {
			pixels[ i ][ j ] = BLACK_CHAR;
		}
	}

	// draw Food
	pixels[ food.x ][ food.y ] = RED_CHAR;

	// draw snake
	for ( int i = 0; i < snake.size(); i++ ) {
		pixels[ snake[ i ].x ][ snake[ i ].y ] = GREEN_CHAR;
	}
}

Position Snake::placeFood() {
	Position p = { int( ofRandom( WIDTH ) ), int( ofRandom( HEIGHT ) ) };
	int tries = 0;
	while ( isInSnake( p ) ) {
		p = { int( ofRandom( WIDTH ) ), int( ofRandom( HEIGHT ) ) };
		tries++;
		if ( tries > 6 ) {
			for ( int i = 0; i < WIDTH; i ++ ) {
				for ( int j = 0; j < HEIGHT; j++ ) {
					if ( pixels[ i ][ j ] == BLACK_CHAR ) p = { i, j };
				}
			}
		}
	}
	return p;
}

bool Snake::isInSnake( Position & p ) {
	bool collide = false;
	for ( int i = 0; i < snake.size(); i++ ) {
		if ( i != snake.size() - 1 && snake[ i ].x == p.x && snake[ i ].y == p.y ) collide = true;
	}
	return collide;
}
