#include "ofApp.h"

void ofApp::setup(){
	ofSetFrameRate( FRAMERATE );

	initGame();

#ifdef USE_SERIAL
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	serial.setup( 0, 57600 );
	serial.flush();
#endif

#ifdef USE_GPIO
	string pins[ 10 ] = {
		GPIO_P1_UP, GPIO_P1_DOWN, GPIO_P1_LEFT, GPIO_P1_RIGHT, GPIO_P1_A,
		GPIO_P2_UP, GPIO_P2_DOWN, GPIO_P2_LEFT, GPIO_P2_RIGHT, GPIO_P2_A
	};
	for ( unsigned int i = 0; i < 10; i++ ) {
		gpios[ i ].setup( pins[ i ] );
		gpios[ i ].export_gpio();
		gpios[ i ].setdir_gpio( "in" );
	}
#endif
}

void ofApp::initGame() {
	if ( gameSelection == 0 ) {
		ofSetFrameRate( 10 );
		game = new Snake();
	}
	else if ( gameSelection == 1 ) {
		ofSetFrameRate( 20 );
		game = new Pong();
	}
	else if ( gameSelection == 2 ) {
		ofSetFrameRate( 10 );
		game = new Tron();
	}
	else if ( gameSelection == 3 ) {
		ofSetFrameRate( 20 );
		game = new Tetris();
	}
	game->setup();

	gameSelection ++;
	gameSelection = gameSelection % NB_GAMES;
}

void ofApp::update(){
#ifdef USE_GPIO
	string tmp = "";
	for ( unsigned int i = 0; i < 10; i++ ) {
		gpios[ i ].getval_gpio( tmp );
		if ( i == 4 || i == 9 ) {
			if ( tmp == "1" ) initGame();
		}
		else {
			game->updateGPIO( i, tmp );
		}
	}
#endif
	game->update();

#ifdef USE_SERIAL
	serialize();
#endif
}

void ofApp::draw() {
#ifdef USE_RENDER
	ofFill();
	for ( unsigned int i = 0; i < 19; i++ ) {
		for ( unsigned int j = 0; j < 11; j++ ) {
			switch ( game->pixels[ j ][ i ] ) {
			case BLACK_CHAR:
				ofSetColor( 0 );
				break;
			case WHITE_CHAR:
				ofSetColor( 255 );
				break;
			case RED_CHAR:
				ofSetColor( 255, 0, 0 );
				break;
			case GREEN_CHAR:
				ofSetColor( 0, 255, 0 );
				break;
			case BLUE_CHAR:
				ofSetColor( 0, 0, 255 );
				break;
			case YELLOW_CHAR:
				ofSetColor( 255, 255, 0 );
				break;
			case CYAN_CHAR:
				ofSetColor( 0, 255, 255 );
				break;
			case PURPLE_CHAR:
				ofSetColor( 255, 0, 255 );
				break;
			case ORANGE_CHAR:
				ofSetColor( 255, 150, 0 );
				break;
			default:
				break;
}
			ofDrawRectangle( j * 20, i * 20, 20, 20 );
		}
	}
#endif
	if ( game->start ) {
		game->start = false;
		ofSleepMillis( 2000 );
	}
}

#ifdef USE_SERIAL
void ofApp::serialize() {
	int index = 0;
	for ( int i = 0; i < 11; i++ ) {
		if ( i % 2 == 0 ) {
			for ( int j = 0; j < 19; j++ ) {
				buf[ index ] = game->pixels[ i ][ 18 - j ];
				index++;
			}
		}
		else {
			for ( int j = 18; j >= 0; j-- ) {
				buf[ index ] = game->pixels[ i ][ 18 - j ];
				index++;
			}
		}
	}

	buf[ 209 ] = '|';

	// serial.writeBytes( &buf[ 0 ], 210 );
	if ( serial.writeBytes( &buf[ 0 ], 210 ) != 210 ) {
		ofLog() << "error sending... ";
	}
}
#endif

#ifdef USE_RENDER
void ofApp::keyPressed( int key ) {
	ofLog() << "keyPressed";
	switch ( key ) {
		case OF_KEY_UP: //P1 Haut [UP]
			ofLog() << "P1 Haut [UP]";
			game->updateGPIO( 0, "1" );
			break;
		case OF_KEY_DOWN: //P1 Bas [DOWN]
			ofLog() << "P1 Bas [DOWN]";
			game->updateGPIO( 1, "1" );
			break;
		case OF_KEY_LEFT: //P1 Gauche [LEFT]
			ofLog() << "P1 Gauche [LEFT]";
			game->updateGPIO( 2, "1" );
			break;
		case OF_KEY_RIGHT: //P1 Droite [RIGHT]
			ofLog() << "P1 Droite [RIGHT]";
			game->updateGPIO( 3, "1" );
			break;
		case 48: //P1 A [0]
			ofLog() << "P1 A [0]";
			//game->updateGPIO( 4, "1" );
			initGame();
			break;

		case 122: //P2 Haut [z]
			ofLog() << "P2 Haut [z]";
			game->updateGPIO( 5, "1" );
			break;
		case 115: //P2 Bas [s]
			ofLog() << "P2 Bas [s]";
			game->updateGPIO( 6, "1" );
			break;
		case 113: //P2 Gauche [q]
			ofLog() << "P2 Gauche [q]";
			game->updateGPIO( 7, "1" );
			break;
		case 100: //P2 Droite [d]
			ofLog() << "P2 Droite [d]";
			game->updateGPIO( 8, "1" );
			break;
		case GLFW_KEY_SPACE: //P2 A [space]
			ofLog() << "P2 A [space]";
			//game->updateGPIO( 9, "1" );
			initGame();
			break;
	}
}

void ofApp::keyReleased( int key ) {
	ofLog() << "keyReleased";
	switch ( key ) {
		case OF_KEY_UP: //P1 Haut [UP]
			ofLog() << "P1 Haut [UP]";
			game->updateGPIO( 0, "0" );
			break;
		case OF_KEY_DOWN: //P1 Bas [DOWN]
			ofLog() << "P1 Bas [DOWN]";
			game->updateGPIO( 1, "0" );
			break;
		case OF_KEY_LEFT: //P1 Gauche [LEFT]
			ofLog() << "P1 Gauche [LEFT]";
			game->updateGPIO( 2, "0" );
			break;
		case OF_KEY_RIGHT: //P1 Droite [RIGHT]
			ofLog() << "P1 Droite [RIGHT]";
			game->updateGPIO( 3, "0" );
			break;
		case 48: //P1 A [0]
			ofLog() << "P1 A [0]";
			game->updateGPIO( 4, "0" );
			break;

		case 122: //P2 Haut [z]
			ofLog() << "P2 Haut [z]";
			game->updateGPIO( 5, "0" );
			break;
		case 115: //P2 Bas [s]
			ofLog() << "P2 Bas [s]";
			game->updateGPIO( 6, "0" );
			break;
		case 113: //P2 Gauche [q]
			ofLog() << "P2 Gauche [q]";
			game->updateGPIO( 7, "0" );
			break;
		case 100: //P2 Droite [d]
			ofLog() << "P2 Droite [d]";
			game->updateGPIO( 8, "0" );
			break;
		case GLFW_KEY_SPACE: //P2 A [space]
			ofLog() << "P2 A [space]";
			game->updateGPIO( 9, "0" );
			break;
	}
}
#endif
