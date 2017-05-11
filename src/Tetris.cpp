#include "Tetris.h"

Tetris::Tetris(){
}

void Tetris::setup() {
	reset();
}

void Tetris::reset() {
	clearBoard();
	resetCompleteMap();
	shape = new Shape( this );
	dropRate = 0.8f;
	lined = false;
}

void Tetris::clearBoard(){
	clearedLines = 0;

	for ( int i = 0; i < WIDTH; i ++ ){
		for ( int j = 0; j < HEIGHT; j ++ ){
			board[ i ][ j ] = '0';
		}
	}
}

void Tetris::deleteFullLines(){
	checkForLines();
	for ( int j = 0; j < HEIGHT; j ++ ) {
		if ( completeLineMap[ j ] == true ) {
			dropDown( j );
		}
	}
}

void Tetris::dropDown( int line ){
	clearedLines++;

	for ( int j = line; j >= 1; j -- ){
		for ( int i = 0; i < WIDTH; i ++ ){
			board[ i ][ j ] = board[ i ][ j - 1 ];
		}
	}

	for ( int i = 0; i < WIDTH; i ++ ) {
		board[ i ][ 0 ] = '0';
	}
}

void Tetris::resetCompleteMap(){
	for ( int j = 0; j < HEIGHT; j ++ ) {
		completeLineMap[ j ] = false;
	}
}

void Tetris::checkForLines(){
	resetCompleteMap();

	for ( int j = 0; j < HEIGHT; j ++ ){
		bool complete = true;
		for ( int i = 0; i < WIDTH; i ++ ){
			if ( board[ i ][ j ] == '0' ) {
				complete = false;
			}
		}
		if( complete ) lined = true;
		completeLineMap[ j ] = complete;
	}
}

void Tetris::update(){
	time += 1.0f / ofGetFrameRate();

	if( lined ){
		lined = false;
		dropRate -= 0.1;
		dropRate = ofClamp( dropRate, 0.1, 0.8 );
		ofLog() << dropRate;
	}

	if ( time > dropRate ){
		shape->moveDown();
		time = 0.0f;
	}
	//ofLog() << shape->x << ' ' << shape->y;
	updatePixels();
}

void Tetris::updateGPIO( int index, string state ) {
	//if ( states[ index ] != state ) {
	Game::states[ index ] = state;

	if ( Game::states[ index ] == "1" ) {
		switch ( index ) {
			case P1_UP:
				if( shape->y > 0 ) shape->rotateRight();
				break;
			case P1_DOWN:
				shape->moveDown();
				break;
			case P1_LEFT:
				shape->moveLeft();
				break;
			case P1_RIGHT:
				shape->moveRight();
				break;
			case P1_A:
				// shape->rotateRight();
				break;
			case P2_UP:
				break;
			case P2_DOWN:
				break;
			case P2_LEFT:
				break;
			case P2_RIGHT:
				break;
			case P2_A:
				break;

			default:
				break;
		}
	}
	//}
}

void Tetris::updatePixels() {
	for ( int i = 0; i < WIDTH; i++ ) {
		for ( int j = 0; j < HEIGHT; j++ ) {
			Game::pixels[ i ][ j ] = BLACK_CHAR;
		}
	}

	// draw board
	for ( int i = 0; i < WIDTH; i ++ ) {
		for ( int j = 0; j < HEIGHT; j ++ ) {
			if ( board[ i ][ j ] != '0' ) {
				Game::pixels[ i ][ j ] = board[ i ][ j ];
			}
		}
	}

	// draw current shape
	for ( int i = 0; i < MAX_SHAPE_SIZE; i ++ ) {
		for ( int j = 0; j < MAX_SHAPE_SIZE; j ++ ) {
			if ( shape->shape[ i ][ j ] != 0 ) {
				if ( shape->x + i >= 0 && shape->x < WIDTH && shape->y >= 0 && shape->y + j <= HEIGHT ) {
					Game::pixels[ shape->x + i ][ shape->y + j ] = shape->color;
				}
			}
		}
	}
}
