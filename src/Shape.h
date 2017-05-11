#pragma once

#include "Tetris.h"

#define MAX_SHAPE_SIZE 4

class Tetris;

class Shape{
	public:
		Shape( Tetris * board );

		void regenerate();
		void update(){};
		void moveLeft();
		void moveRight();
		void moveDown();
		void dropDown();

		void rotateRight();
		void rotateLeft();

		bool testCollision();
		bool testTempCollision();
		void printOnBoard();

		int x, y;
		int shape[ MAX_SHAPE_SIZE ][ MAX_SHAPE_SIZE ];
		int t[ MAX_SHAPE_SIZE ][ MAX_SHAPE_SIZE ];

		bool falling;
		bool fresh;
		Tetris * tetris;
		char color;
};
