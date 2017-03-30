#include "ofApp.h"

void ofApp::setup(){
	ofHideCursor();
	ofSetFrameRate( 10 );
	ofBackground( 255, 255, 0 );
	//ofSetWindowShape( 11*SCALE, 19*SCALE );
	//ofSetWindowPosition( 10, 100 );

	fbo.allocate( WIDTH , HEIGHT, GL_RGB );

	fbo.begin();
		ofSetColor( 255 );
		ofClear( 255, 255, 255, 0 );
		ofFill();
	fbo.end();

	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	serial.setup( 0, 115200 );
	serial.flush();

	game.setup();

}

void ofApp::update(){
	game.update();
	updateFbo();
	getPixels();
	serialize();
}

void ofApp::draw(){
	fbo.draw( 0, 0 );
}

void ofApp::updateFbo(){
	fbo.begin();
		ofBackground( 255 );
		//game.draw();
	fbo.end();

	fbo.readToPixels( fboPixels );
	//img.setFromPixels( fboPixels );
}

void ofApp::getPixels(){
	for( unsigned int i = 0; i < 19; i ++ ) {
        for( unsigned int j = 0; j < 11; j ++ ) {
			a[ i ][ j ] = fboPixels.getColor( j, i ).r > 100;
        }
    }
}

void ofApp::serialize() {
	int index = 0;
	for( int i = 18; i >= 0; i-- ){
		if( i % 2 == 0 ){
			for ( int j = 0; j < 11; j++ ){
				buf[ index ] = a[ i ][ j ] ? '1' : '0';
				index ++;
			}
		}
		else{
			for( int j = 10; j >= 0; j-- ){
				buf[ index ] = a[ i ][ j ] ? '1' : '0';
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