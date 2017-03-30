#include "ofApp.h"

void ofApp::setup(){
	ofHideCursor();
	ofSetFrameRate( 20 );

	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	serial.setup( 0, 115200 );
	serial.flush();

	game.setup();
}

void ofApp::update(){
	game.update();
	serialize();
}

void ofApp::draw(){
	ofFill();
	for ( unsigned int i = 0; i < 19; i++ ) {
		for ( unsigned int j = 0; j < 11; j ++ ) {
			ofSetColor( game.pixels.getColor( j, i ) );
			ofDrawRectangle( j * 20, i * 20, 20, 20 );
		}
	}
}

void ofApp::serialize() {
	int index = 0;
	for( int i = 18; i >= 0; i-- ){
		if( i % 2 == 0 ){
			for ( int j = 0; j < 11; j++ ){
				buf[ index ] = ( game.pixels.getColor( j, i ).r == 255 ? '1' : '0' );
				index ++;
			}
		}
		else{
			for( int j = 10; j >= 0; j-- ){
				buf[ index ] = ( game.pixels.getColor( j, i ).r == 255 ? '1' : '0' );
				index ++;
			}
		}
	}

	buf[ 209 ] = '|';

	// serial.writeBytes( &buf[ 0 ], 210 );
	if ( serial.writeBytes( &buf[ 0 ], 210 ) != 210 ) {
		ofLog() << "error sending... ";
	}
}