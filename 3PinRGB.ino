/**
 * @file 3PinRGB.ino
 *
 * @brief This code lets you use your Arduino for controlling
 * a 3 pin addressable LED strip, originally designed to work
 * with an RGB computer fan where the strip is a ring
 *
 * @author Daniel Szabo
 * Contact: dszabo99@icloud.com
 *
 */

#include <FastLED.h>

// !!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! STEP 1 PLEASE READ !!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!

// 1. set this to the digital pin the RGB strip is connected to
#define   LED_PIN        3
// 2. set this to the number of LEDs on the RGB strip
#define   NUM_LEDS       15
// 3. set this to a number between 0 and 100 to set a brightness
#define   BRIGHTNESS     100

// array used by the FastLED library
CRGB leds[NUM_LEDS];
// array used by this code for simplicity
int ledColours[NUM_LEDS][3];
// array containing 8 basic colours
int colours[][3] = {255,255,255,  0,0,0,  255,0,0,  0,255,0,  0,0,255,  0,127,255,  255,127,127,  127,0,255};
// global iterating variable and brightness value
int n = 0, brightnessMultiplier = 100;
// 6 constants for 6 speed settings
int SLOWEST = 0, SLOWER = 1, SLOW = 2, MEDIUM = 3, FAST = 3, FASTER = 4, FASTEST = 5;
// 8 constants for 8 basic colours
int WHITE = 0, BLACK = 1, RED = 2, GREEN = 3, BLUE = 4, TURQUOISE = 5, YELLOW = 6, PURPLE = 7;
// 2 constants for 2 animation directions
int FORWARD = 1, BACKWARD = -1;


// setting up stuff
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!
// !!! STEP 2 PLEASE READ !!!!
// !!!!!!!!!!!!!!!!!!!!!!!!!!!

// This is where you can choose 
// - lighting mode
// - colour(s)
// - animation speed
// - animation direction.
// You enable a lighting mode by uncommenting its function call (removing the '//' in front of it).
// Only 1 animation mode can be enabled, less or more will break the controller.
// Each lighting mode has different parameters, follow the examples.
// You can use predefined colours ; WHITE, BLACK, RED, GREEN, TURQUOISE, YELLOW, PURPLE,
// or you can use custom colours by defining Red, Green and Blue values from 0 to 255, follow the examples provided.
// Where applicable, the animation speeds are SLOWEST, SLOWER, SLOW, MEDIUM, FAST, FASTER and FASTEST.
// Where applicable, the animation directions are FORWARD and BACKWARD.

void loop() {
  /* ( MODE 1 ) only one colour, no changes */
  //solidColour(RED);
  solidColour(0, 120, 255);


  /* ( MODE 2 ) pulsing colour, only one colour */
  //pulse(TURQUOISE, FAST);
  //pulse(255, 0, 255, FAST);


  /* ( MODE 3 ) fading with two colours, */
  //circleMulticolour(255,127,0,  255,31,255, FAST);
  //circleMulticolour(WHITE, TURQUOISE, MEDIUM);


  /* ( MODE 4 ) circling, only one colour */
  //circle(WHITE, SLOW, FORWARD);
  //circle(255, 127, 0, MEDIUM, BACKWARD);


  /* ( MODE 5 ) circling, two colours */
  //circleTwoColours(RED, BLUE, FAST, FORWARD);
  //circleTwoColours(0,0,255, 100,0,150, SLOW, FORWARD);


  /* ( MODE 6 ) each LED going through rainbow together */
  //solidRainbow(SLOWEST);
  //solidRainbow(FAST);


  /* ( MODE 7 ) LEDs going through rainbow in waves */
  //circleRainbow(MEDIUM, FORWARD);
  //circleRainbow2(MEDIUM, BACKWARD);
  //circleRainbow3(MEDIUM, FORWARD);
}

// -------------------
// lighting modes
// -------------------

/* ( MODE 1 ) only one colour, no changes */
/** Wrapper for the other solidColour(), this one takes a predefined colour
*
* @param colour colour from predefined 8 colours
*/
void solidColour(int colour){
  solidColour(colours[colour][0], colours[colour][1], colours[colour][2]);
}

/** One colour, no animation
*
* @param red red value 
* @param green green value 
* @param blue blue value 
*/
void solidColour(int red, int green, int blue){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, red, green, blue);
  }
  delay(100000);
}

/* ( MODE 2 ) pulsing colour, only one colour */
/** Wrapper for the other pulse(), this one takes a predefined colour
*
* @param colour colour from predefined 8 colours
* @param speed speed of animation
*/
void pulse(int colour, int speed){
  pulse(colours[colour][0], colours[colour][1], colours[colour][2], speed);
}

/** One colour turning on and off smoothly
*
* @param red red value 
* @param green green value 
* @param blue blue value 
* @param speed speed of animation
*/
void pulse(int red, int green, int blue, int speed){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, sin(n, red), sin(n, green), sin(n, blue));
  }
  incrementN(speed, FORWARD);
}


/* ( MODE 3 ) fading with two colours, */
/** Wrapper for the other circle(), this one takes 2 predefined colours
*
* @param colour1 colour 1 from predefined 8 colours
* @param colour2 colour 2 from predefined 8 colours
* @param speed speed of animation
* @param direction direction of flow
*/
void fadeTwoColours( int colour1, int colour2, int speed, int direction){
  fadeTwoColours(colours[colour1][0], colours[colour1][1], colours[colour1][2], 
                    colours[colour2][0], colours[colour2][1], colours[colour2][2], speed);
}

/** whole strip changing between two colours smoothly
*
* @param red1 red value 1
* @param green1 green value 1
* @param blue1 blue value 1
* @param red2 red value 2
* @param green2 green value 2
* @param blue2 blue value 2
* @param speed speed of animation
* @param direction direction of flow
*/
void fadeTwoColours( int red1, int green1, int blue1,
                        int red2, int green2, int blue2, int speed){

  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, 
      mixValues(red1, red2, sin1(n)) ,
      mixValues(green1, green2, sin1(n)) ,
      mixValues(blue1, blue2, sin1(n)));
  }

  incrementN(speed, FORWARD);
}

/* ( MODE 4 ) circling, only one colour */
/** Wrapper for the other circle(), this one takes a predefined colour
*
* @param colour colour from predefined 8 colours
* @param speed speed of animation
* @param direction direction of flow
*/
void circle(int colour, int speed, int direction){
  circle(colours[colour][0], colours[colour][1], colours[colour][2], speed, direction);
}

/** One colour going around
*
* @param red red value 
* @param green green value 
* @param blue blue value 
* @param speed speed of animation
* @param direction direction of flow
*/
void circle(int red, int green, int blue, int speed, int direction){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, sin(n+i*24, red), sin(n+i*24, green), sin(n+i*24, blue));
  }
  incrementN(speed, direction);
}


/* ( MODE 5 ) circling, two colours */
/** Wrapper for the other circleTwoColours(), this one takes predefined colours
*
* @param colour1 colour 1 from predefined 8 colours
* @param colour2 colour 2 from predefined 8 colours
* @param speed speed of animation
* @param direction direction of flow
*/
void circleTwoColours( int colour1, int colour2, int speed, int direction){
  circleTwoColours(colours[colour1][0], colours[colour1][1], colours[colour1][2], 
                    colours[colour2][0], colours[colour2][1], colours[colour2][2], speed, direction);
}

/** Two colours going around
*
* @param red1 red value 1
* @param green1 green value 1
* @param blue1 blue value 1
* @param red2 red value 2
* @param green2 green value 2
* @param blue2 blue value 2
* @param speed speed of animation
* @param direction direction of flow
*/
void circleTwoColours( int red1, int green1, int blue1,
                      int red2, int green2, int blue2, int speed, int direction){

  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, 
      mixValues(red1, red2, sin1(n+i*24)) ,
      mixValues(green1, green2, sin1(n+i*24)) ,
      mixValues(blue1, blue2, sin1(n+i*24)));
  }

  incrementN(speed, direction);
}


/* ( MODE 6 ) each LED going through rainbow together */
/** each LED going through rainbow together
*
* @param speed speed of animation
*/
void solidRainbow(int speed){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, sin255(n), sin255(n+120), sin255(n+240));
  }
  incrementN(speed, FORWARD);
}


/* ( MODE 7 ) LEDs going through rainbow in waves */
/** Standard rainbow going around
*
* @param speed speed of animation
* @param direction direction of flow
*/
void circleRainbow(int speed, int direction){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, sin255(n+i*24), sin255(n+i*24+120), sin255(n+i*24+240));
  }
  incrementN(speed/4, direction);
}

/** Funny rainbow going around
*
* @param speed speed of animation
* @param direction direction of flow
*/
void circleRainbow2(int speed, int direction){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, sin255(n+i*6), sin255(n+i*0), sin255(n+i*24));
  }
  incrementN(speed, direction);
}

/** Funny rainbow going around
*
* @param speed speed of animation
* @param direction direction of flow
*/
void circleRainbow3(int speed, int direction){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, sin255(n+i*2), sin255(n+i*6), sin255(n+i*0));
  }
  incrementN(speed, direction);
}

// -------------------
// main helper methods 
// -------------------

/** sets max brightness value
*
* @param b brightness from 0 to 100
*/
void brightness(int b){
  brightnessMultiplier = b%101;
}

/** generates a colour (3 element int array) from 3 arguments
*
* @param red red value
* @param green green value
* @param blue blue value
*/
int* custom(int red, int green, int blue){
  int customRGB[3] = {red, green, blue};
  return customRGB;
}

/** increments the counter for animations by the defined rate 
*
* @param speed speed value from 0 to 5, referring to speed constants at the top of file
* @param b direction for changing n, 1 is adding, -1 is taking away
*/
void incrementN(int speed, int direction){
  if(speed == SLOWEST) n+=1*direction;
  else if(speed == SLOWER) n+=2*direction;
  else if(speed == SLOW) n+=4*direction;
  else if(speed == MEDIUM) n+=8*direction;
  else if(speed == FAST) n+=16*direction;
  else if(speed == FASTER) n+=32*direction;
  else if(speed == FASTEST) n+=64*direction;
}

/** Gives back the weighted average of two colours
*
* @param red1 first red value
* @param red2 second red value
* @param green1 first green value
* @param green2 second green value
* @param blue1 first blue value
* @param blue2 second blue value
* @param ratio ratio of the two colours, 0 is max weight on a, 1 is max weight on b
*/
int* mixColours( int red1, int green1, int blue1,
                  int red2, int green2, int blue2, float ratio){
    int mixedColour[3] = {mixValues(red1, red2, ratio),
                          mixValues(green1, green2, ratio),
                          mixValues(blue1, blue2, ratio)};
    return mixedColour;
}


/** Gives back the weighted average of two integers
*
* @param a first value
* @param b second value
* @param ratio ratio of the two numbers, 0 is max weight on a, 1 is max weight on b
*/
int mixValues(int a, int b, float ratio){
  if(ratio >= 0 && ratio <= 1){
    return a*(1-ratio)+b*(ratio);
  } else if (ratio > 1){
    return a;
  } else {
    return b;
  }
  
}

/** Gives a value from 0 to 1 based on the angle given
*
* @param angle angle in degrees
*/
float sin1(float angle){
  return sin(angle, 1);
}

/** Gives a value from 0 to 255 based on the angle given
*
* @param angle angle in degrees
*/
float sin255(float angle){
  return sin(angle, 255);
}

/** Gives a value from 0 to multiplier based on the angle given
*
* @param angle angle in degrees
* @param multiplier maximum value
*/
float sin(float angle, float multiplier){
  multiplier/=2;
  float rad = angle*PI/180;
  return multiplier+sin(rad)*multiplier;
}


/** Submits the current leds list and it shows up on the strip */
void show(){
  FastLED.show();
}

/** Set a specified LED's colour 
*
* Takes R, G and B values, and applies the colour to the specified LED, also considering the brightness value 
*
* @param led index of the LED we are setting
* @param red red colour value 0-255
* @param green green colour value 0-255
* @param blue blue colour value 0-255
*/
void setLedColour(int led, int red, int green, int blue){
  float multiplier = brightnessMultiplier/100.0f;
  leds[led%NUM_LEDS] = CRGB((red%256)*multiplier, (green%256)*multiplier, (blue%256)*multiplier);
  show();
}

