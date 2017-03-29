#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofHideCursor();
	ofSetFrameRate( 5 );
	ofBackground( 30 );
	play = true;

	fbo.allocate( 110, 190, GL_RGB );
	fbo.begin();
		ofSetColor( 255 );
		ofClear( 255, 255, 255, 0 );
		ofFill();
	fbo.end();

	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	serial.setup();
	serial.flush();
}

//--------------------------------------------------------------
void ofApp::update(){
	if( play ) randomize();
}

//--------------------------------------------------------------
void ofApp::draw(){
	if ( play ) {
		for( int i = 0; i < 19; i ++ ) {
			for( unsigned int j = 0; j < 11; j ++ ) {
				if( a[ i ][ j ] ) ofDrawRectangle( j * 10, i * 10, 10, 10 );
			}
		}

		serialize();
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	play = !play;
}

void ofApp::randomize(){
	for( unsigned int i = 0; i < 19; i ++ ) {
        for( unsigned int j = 0; j < 11; j ++ ) {
            a[ i ][ j ] = ofRandom( 1 ) > .5;
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
