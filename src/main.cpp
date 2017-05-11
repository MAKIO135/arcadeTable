//#define USE_RENDER

#include "ofMain.h"
#include "ofApp.h"
#ifndef USE_RENDER
#include "ofAppNoWindow.h"
#endif

int main( ){
#ifndef USE_RENDER
    ofAppNoWindow window;
	ofSetupOpenGL( &window, 0, 0, OF_WINDOW );
#else
	ofSetupOpenGL( 220, 380, OF_WINDOW );
#endif
	ofRunApp( new ofApp() );
}
