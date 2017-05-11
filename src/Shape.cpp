#include "Shape.h"

Shape::Shape( Tetris * board ){
	ofSeedRandom( ofGetElapsedTimeMillis() );
	tetris = board;
	regenerate();
}

void Shape::regenerate(){
	x = WIDTH / 2 - MAX_SHAPE_SIZE / 2;
	y = - MAX_SHAPE_SIZE + 1;

	int tiles = 0;
	int patterns[ 7 ][ 4 ][ 4 ] = {
		{
			{ 0,1,0,0 },
			{ 0,1,0,0 },
			{ 0,1,0,0 },
			{ 0,1,0,0 }
		},
		{
			{ 0,0,0,0 },
			{ 0,1,1,0 },
			{ 0,1,1,0 },
			{ 0,0,0,0 }
		},
		{
			{ 0,0,0,0 },
			{ 0,1,0,0 },
			{ 0,1,1,1 },
			{ 0,0,0,0 }
		},
		{
			{ 0,0,0,0 },
			{ 0,0,1,0 },
			{ 1,1,1,0 },
			{ 0,0,0,0 }
		},
		{
			{ 0,0,0,0 },
			{ 0,1,0,0 },
			{ 0,1,1,0 },
			{ 0,0,1,0 }
		},
		{
			{ 0,0,0,0 },
			{ 0,0,1,0 },
			{ 0,1,1,0 },
			{ 0,1,0,0 }
		},
		{
			{ 0,0,0,0 },
			{ 0,1,0,0 },
			{ 1,1,1,0 },
			{ 0,0,0,0 }
		}
	};

	int choice = floor( ofRandom( 7 ) );
	string tmp;
	ostringstream convert;
	convert << (choice + 2);
	tmp = convert.str();
	color = tmp.at( 0 );
	// ofLog() << "color:" << color;

	for ( int i = 0; i < MAX_SHAPE_SIZE; i++ ) {
		for ( int j = 0; j < MAX_SHAPE_SIZE; j++ ) {
			shape[ i ][ j ] = patterns[ choice ][ i ][ j ];
			tiles++;
		}
	}

	fresh = true;
	falling = true;
}

bool Shape::testCollision(){
	int collide = false;

	for ( int i = 0; i < MAX_SHAPE_SIZE; i ++ ){
		for ( int j = 0; j < MAX_SHAPE_SIZE; j ++ ){

			int xx = i+x;
			int yy = j+y;

			if ( xx >= 0 && xx < WIDTH && yy >= 0 && yy < HEIGHT ){
				if ( tetris->board[ xx ][ yy ] == '0' || shape[ i ][ j ] == 0 ){
					//good, no collision on this tile
				}
				else{
					collide = true;
					break;
				}
			}

			if ( shape[ i ][ j ] != 0 && yy >= HEIGHT ||
				shape[ i ][ j ] != 0 && xx < 0 ||
				shape[ i ][ j ] != 0 && xx >= WIDTH ) {
				collide = true;
			}
		}
	}

	return collide;	//collision
}

bool Shape::testTempCollision(){
	int collide = false;

	for ( int i = 0; i < MAX_SHAPE_SIZE; i ++ ){
		for ( int j = 0; j < MAX_SHAPE_SIZE; j ++ ){

			int xx = i+x;
			int yy = j+y;

			if ( xx >= 0 && xx < WIDTH && yy >= 0 && yy < HEIGHT ){
				if ( tetris->board[ xx ][ yy ] == '0' || t[ i ][ j ] == 0 ){
					//good, no collision on this tile
				}
				else{
					collide = true;
					break;
				}
			}

			if ( t[ i ][ j ] != 0 && yy >= HEIGHT ||
				t[ i ][ j ] != 0 && xx < 0 ||
				t[ i ][ j ] != 0 && xx >= WIDTH ) {
				collide = true;
			}
		}
	}

	return collide;	//collision
}

void Shape::printOnBoard(){
	for ( int i = 0; i < MAX_SHAPE_SIZE; i ++ ){
		for ( int j = 0; j < MAX_SHAPE_SIZE; j ++ ){
			if ( tetris->board[ i + x ][ j + y ] == '0' ) {
				tetris->board[ i + x ][ j + y ] = shape[ i ][ j ] == 1 ? color : '0';
			}
		}
	}
}

void Shape::rotateLeft(){
	int t[ MAX_SHAPE_SIZE ][ MAX_SHAPE_SIZE ];

	for ( int i = 0; i < MAX_SHAPE_SIZE; i ++ ){
		for ( int j = 0; j < MAX_SHAPE_SIZE; j ++ ){
			t[ i ][ j ] = shape[ MAX_SHAPE_SIZE - j - 1 ][ i ];
		}
	}

	for ( int i = 0; i < MAX_SHAPE_SIZE; i ++ ){
		for ( int j = 0; j < MAX_SHAPE_SIZE; j ++ ){
			shape[ i ][ j ]= t[ i ][ j ];
			if ( shape[ i ][ j ] == 1 && x <= 0 ) x = 0;
		}
	}
}

void Shape::rotateRight(){
	for ( int i = 0; i < MAX_SHAPE_SIZE; i++ ){
		for ( int j = 0; j < MAX_SHAPE_SIZE; j++ ){
			t[ i ][ j ] = shape[ j ][ MAX_SHAPE_SIZE - i - 1 ];
		}
	}

	if( !testTempCollision() ){
		for ( int i = 0; i < MAX_SHAPE_SIZE; i++ ){
			for ( int j = 0; j < MAX_SHAPE_SIZE; j++ ){
				shape[ i ][ j ] = t[ i ][ j ];
				if ( shape[ i ][ j ] == 1 && x + i >= WIDTH ) x = WIDTH - 1 - i;
				if ( shape[ i ][ j ] == 1 && x <= 0 ) x = 0;
			}
		}
	}
}

void Shape::moveLeft(){
	fresh = false;
	x--;

	if ( testCollision() == true ) { //we collide
		x++;
	}
}

void Shape::moveRight(){
	fresh = false;
	x++;

	if ( testCollision() == true ) {//we collide
		x--;
	}
}

void Shape::moveDown(){
	fresh = false;
	y++;

	if( testCollision() == true ){ //we collide
		y--;
		falling = false;
		printOnBoard();

		tetris->deleteFullLines();
		if( y == - MAX_SHAPE_SIZE + 1 ){
			tetris->reset();
			tetris->start = true;
		}
		regenerate();
	}
}

void Shape::dropDown(){
	fresh = false;
	while ( fresh == false ){
		moveDown();
	}
}
