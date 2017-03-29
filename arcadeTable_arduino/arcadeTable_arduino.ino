#include <Adafruit_NeoPixel.h>
#define PIN 6
#define NUMPIXELS 209

Adafruit_NeoPixel strip = Adafruit_NeoPixel( NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800 );

void setup() {
  Serial.begin( 115200 );
  strip.begin();
  strip.show();
}

void loop() {
}

void serialEvent() {
  static unsigned char index = 0;
  
  if ( Serial.available() ) {
    char inChar = ( char ) Serial.read();
    while ( inChar != '|' ) {
      if ( Serial.available() ) {
        inChar = ( char ) Serial.read();
        //Serial.print( inChar );

        if ( inChar == '0') {
          strip.setPixelColor( index, strip.Color( 0, 0, 0 ) );
        }
        else if ( inChar == '1') {
          strip.setPixelColor( index, strip.Color( 255, 255, 255 ) );
        }
        else if ( inChar == '|' ) {
          //Serial.print( index );
          //Serial.print( '|' );
          index = 0;
          strip.show();
        }

        index ++;
      }
    }
  }
}

