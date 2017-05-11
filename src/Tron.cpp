#include "Tron.h"

Tron::Tron(){
}

void Tron::setup() {
	reset();
}

void Tron::reset() {
	food = placeFood();

	vx = 0;
	vy = 1;

	snake.clear();
	for ( int i = 0; i < 3; i++ ) {
		snake.push_back( { 3, 5 - i * vy } );
	}

	vx2 = 0;
	vy2 = -1;

	snake2.clear();
	for ( int i = 0; i < 3; i++ ) {
		snake2.push_back( { 7, 5 - i * vy2 } );
	}
}

void Tron::update() {
	Position first = { ( snake[ 0 ].x + vx + WIDTH ) % WIDTH, ( snake[ 0 ].y + vy + HEIGHT ) % HEIGHT };
	Position first2 = { ( snake2[ 0 ].x + vx2 + WIDTH ) % WIDTH, ( snake2[ 0 ].y + vy2 + HEIGHT ) % HEIGHT };

	if ( isInSnake( first ) || isInSnake2( first ) || isInSnake( first2 ) || isInSnake2( first2 ) ) {
		ofSleepMillis( 3000 );
		reset();
	}
	else {
		vector<Position>::iterator it = snake.begin();
		snake.insert( it, first );

		if ( snake[ 0 ].x == food.x && snake[ 0 ].y == food.y ) food = placeFood();
		else snake.pop_back();


		vector<Position>::iterator it2 = snake2.begin();
		snake2.insert( it2, first2 );

		if ( snake2[ 0 ].x == food.x && snake2[ 0 ].y == food.y ) food = placeFood();
		else snake2.pop_back();

		updatePixels();

		vitChanged = true;
		vitChanged2 = true;
	}
}

void Tron::updateGPIO( int index, string state ) {
	if ( states[ index ] != state ) {
		Game::states[ index ] = state;

		if ( Game::states[ index ] == "1" ) {
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
				if ( vy2 != -1 ) {
					vx2 = 0;
					vy2 = 1;
					vitChanged2 = false;
				}
				break;
			case P2_DOWN:
				if ( vy2 != 1 ) {
					vx2 = 0;
					vy2 = -1;
					vitChanged2 = false;
				}
				break;
			case P2_LEFT:
				if ( vx2 != -1 ) {
					vx2 = 1;
					vy2 = 0;
					vitChanged2 = false;
				}
				break;
			case P2_RIGHT:
				if ( vx2 != 1 ) {
					vx2 = -1;
					vy2 = 0;
					vitChanged2 = false;
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

void Tron::updatePixels(){
	for ( int i = 0; i < WIDTH; i ++ ) {
		for ( int j = 0; j < HEIGHT; j ++ ) {
			Game::pixels[ i ][ j ] = BLACK_CHAR;
		}
	}

	// draw Food
	Game::pixels[ food.x ][ food.y ] = YELLOW_CHAR;

	// draw snake
	for ( int i = 0; i < snake.size(); i++ ) {
		Game::pixels[ snake[ i ].x ][ snake[ i ].y ] = BLUE_CHAR;
	}

	// draw snake2
	for ( int i = 0; i < snake2.size(); i++ ) {
		Game::pixels[ snake2[ i ].x ][ snake2[ i ].y ] = RED_CHAR;
	}
}

Position Tron::placeFood() {
	Position p = { int( ofRandom( WIDTH ) ), int( ofRandom( HEIGHT ) ) };
	int tries = 0;
	while ( isInSnake( p ) || isInSnake( p ) ) {
		p = { int( ofRandom( WIDTH ) ), int( ofRandom( HEIGHT ) ) };
		tries++;
		if ( tries > 6 ) {
			for ( int i = 0; i < WIDTH; i ++ ) {
				for ( int j = 0; j < HEIGHT; j++ ) {
					if ( Game::pixels[ i ][ j ] == BLACK_CHAR ) p = { i, j };
				}
			}
		}
	}
	return p;
}

bool Tron::isInSnake( Position & p ) {
	bool collide = false;
	for ( int i = 0; i < snake.size(); i++ ) {
		if ( i != snake.size() - 1 && snake[ i ].x == p.x && snake[ i ].y == p.y ) collide = true;
	}
	return collide;
}

bool Tron::isInSnake2( Position & p ) {
	bool collide = false;
	for ( int i = 0; i < snake2.size(); i++ ) {
		if ( i != snake2.size() - 1 && snake2[ i ].x == p.x && snake2[ i ].y == p.y ) collide = true;
	}
	return collide;
}
