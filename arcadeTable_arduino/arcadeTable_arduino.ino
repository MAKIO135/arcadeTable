#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 209

#define WIDTH 19
#define HEIGHT 11

#define BLACK strip.Color( 0, 0, 0 )
#define WHITE strip.Color( 255, 255, 255 )
#define RED strip.Color( 255, 0, 0 )
#define GREEN strip.Color( 0, 255, 0 )
#define BLUE strip.Color( 0, 0, 255 )
#define YELLOW strip.Color( 255, 255, 0 )
#define CYAN strip.Color( 0, 255, 255 )
#define PURPLE strip.Color( 255, 0, 255 )
#define ORANGE strip.Color( 255, 120, 0 )

Adafruit_NeoPixel strip = Adafruit_NeoPixel( NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800 );
unsigned char index = 0;

bool boot = true;

void setup() {
    Serial.begin( 57600 );
    strip.begin();
    strip.show();
}

void loop() {
    if( boot ) {
        for( int i = 0; i < NUMPIXELS; i++ ) {
            strip.setPixelColor( i, BLACK );
        }

        int line = ( millis() / 200 ) % WIDTH;
        int startIndex = line * HEIGHT;
        for( int i = 0; i < HEIGHT; i ++ ) {
            strip.setPixelColor( i + startIndex, ORANGE );
        }
        strip.show();
    }
}

void serialEvent() {
    while ( Serial.available() ) {
        char inChar = ( char ) Serial.read();
        //Serial.print( inChar );

        switch ( inChar ) {
            case '0': // BLACK
                strip.setPixelColor( index, BLACK );
                break;
            case '1': // WHITE
                strip.setPixelColor( index, WHITE );
                break;
            case '2': // RED
                strip.setPixelColor( index, RED );
                break;
            case '3': // GREEN
                strip.setPixelColor( index, GREEN );
                break;
            case '4': // BLUE
                strip.setPixelColor( index, BLUE );
                break;
            case '5': // YELLOW
                strip.setPixelColor( index, YELLOW );
                break;
            case '6': // CYAN
                strip.setPixelColor( index, CYAN );
                break;
            case '7': // PURPLE
                strip.setPixelColor( index, PURPLE );
                break;
            case '8': // ORANGE
                strip.setPixelColor( index, ORANGE );
                break;
            case '|':
                boot = false;
                strip.show();
                break;
        }

        if ( inChar == '|' ) index = 0;
        else index++;
    }
}
