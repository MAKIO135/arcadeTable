#pragma once

#include "ofMain.h"
#include "Game.h"
#include "Shape.h"

#define NUM_PATTERNS 7	/*[1..6]*/

class Shape;

class Tetris : public Game{
	public:
		Tetris();
		virtual void setup();
		virtual void update();
		virtual void updateGPIO( int index, string state );

		void deleteFullLines();
		void reset();
		char board[ WIDTH ][ HEIGHT ];

	private:
		void updatePixels();

		void clearBoard();
		void resetCompleteMap();
		void dropDown( int line );	//this erases a full line, and drops everything down
		void checkForLines();
		int getClearedLines(){ return clearedLines;	};

		Shape * shape;
		bool completeLineMap[ HEIGHT ];
		float time;
		int clearedLines;
		float dropRate;
		bool lined;
};
