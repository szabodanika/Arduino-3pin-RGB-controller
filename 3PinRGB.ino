#include <FastLED.h>
#define LED_PIN     3
#define NUM_LEDS    15
CRGB leds[NUM_LEDS];

int ledColours[NUM_LEDS][3];
int colours[][3] = {
  255,255,255,  0,0,0,  255,0,0,  0,255,0,
  0,0,255,  0,127,255,  255,127,127,  127,0,255
};
int n = 0, r = 0, g = 0, b = 0, brightnessMultiplier = 100;
int SLOWEST = 0, SLOWER = 1, SLOW = 2, MEDIUM = 3, FAST = 3, FASTER = 4, FASTEST = 5;
int WHITE = 0, BLACK = 1, RED = 2, GREEN = 3, BLUE = 4, TURQUOISE = 5, YELLOW = 6, purple = 7;
int FORWARD = 1, BACKWARD = -1;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {

  /* ( OPTIONAL ) set bightness value from 0 to 100, default is 100 */
  brightness(100);

  /* ( MODE 1 ) only one colour, no changes */
  //solidColour(RED);

  /* ( MODE 2 ) pulsing colour, only one colour */
  //pulse(TURQUOISE, FAST);
  //pulse(255, 0, 255, FAST);

  /* ( MODE 3 ) fading with two colours, */
  //circleMulticolour(255,127,0,  255,31,255, FAST);
  //circleMulticolour(WHITE, TURQUOISE, MEDIUM);

  /* ( MODE 4 ) circling, only one colour */
  //circle(WHITE, SLOW, FORWARD);
  //circle(255, 127, 0, MEDIUM, BACKWARD);

  /* ( MODE 5 ) circling, multiple colours (max 5) */
  //circleTwoColours(RED, BLUE, FAST, FORWARD);
  circleTwoColours(0,0,255, 100,0,150, SLOW, FORWARD);

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

void solidColour(int colour){
  solidColour(colours[colour][0], colours[colour][1], colours[colour][2]);
}

void solidColour(int red, int green, int blue){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, red, green, blue);
  }
  delay(100000);
}

void pulse(int colour, int speed){
  pulse(colours[colour][0], colours[colour][1], colours[colour][2], speed);
}

void pulse(int red, int green, int blue, int speed){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, sin255(n, red), sin255(n, green), sin255(n, blue));
  }
  incrementN(speed, FORWARD);
}

void fadeTwoColours( int colour1, int colour2, int speed, int direction){
  fadeTwoColours(colours[colour1][0], colours[colour1][1], colours[colour1][2], 
                    colours[colour2][0], colours[colour2][1], colours[colour2][2], speed);
}

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

void circle(int colour, int speed, int direction){
  circle(colours[colour][0], colours[colour][1], colours[colour][2], speed, direction);
}

void circle(int red, int green, int blue, int speed, int direction){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, sin255(n+i*24, red), sin255(n+i*24, green), sin255(n+i*24, blue));
  }
  incrementN(speed, direction);
}

void circleTwoColours( int colour1, int colour2, int speed, int direction){
  circleTwoColours(colours[colour1][0], colours[colour1][1], colours[colour1][2], 
                    colours[colour2][0], colours[colour2][1], colours[colour2][2], speed, direction);
}

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

void solidRainbow(int speed){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, sin255(n), sin255(n+120), sin255(n+240));
  }
  incrementN(speed, FORWARD);
}

void circleRainbow(int speed, int direction){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, sin255(n+i*24), sin255(n+i*24+120), sin255(n+i*24+240));
  }
  incrementN(speed/4, direction);
}

void circleRainbow2(int speed, int direction){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, sin255(n+i*6), sin255(n+i*0), sin255(n+i*24));
  }
  incrementN(speed, direction);
}

void circleRainbow3(int speed, int direction){
  for(int i = 0; i < NUM_LEDS; i++){
    setLedColour(i, sin255(n+i*2), sin255(n+i*6), sin255(n+i*0));
  }
  incrementN(speed, direction);
}

// -------------------
// main helper methods 
// -------------------

void brightness(int b){
  brightnessMultiplier = b%101;
}

int* custom(int red, int green, int blue){
  int customRGB[3] = {red, green, blue};
  return customRGB;
}

void incrementN(int speed, int direction){
  if(speed == SLOWEST) n+=1*direction;
  else if(speed == SLOWER) n+=2*direction;
  else if(speed == SLOW) n+=4*direction;
  else if(speed == MEDIUM) n+=8*direction;
  else if(speed == FAST) n+=16*direction;
  else if(speed == FASTER) n+=32*direction;
  else if(speed == FASTEST) n+=64*direction;
}

int* mixColours( int red1, int green1, int blue1,
                  int red2, int green2, int blue2, float ratio){
    int mixedColour[3] = {mixValues(red1, red2, ratio),
                          mixValues(green1, green2, ratio),
                          mixValues(blue1, blue2, ratio)};
    return mixedColour;
}

int mixValues(int a, int b, float ratio){
  if(ratio >= 0 && ratio <= 1){
    return a*(1-ratio)+b*(ratio);
  } else if (ratio > 1){
    return a;
  } else {
    return b;
  }
  
}

float sin1(float angle){
  float rad = angle*PI/180;
  return 0.5+sin(rad)*0.5;
}

float sin255(float angle){
  float rad = angle*PI/180;
  return 128+sin(rad)*127;
}

float sin255(float angle, int multiplier){
  multiplier/=2;
  float rad = angle*PI/180;
  return multiplier+sin(rad)*multiplier;
}

void show(){
  FastLED.show();
}

void setLedColour(int led, int red, int green, int blue){
  float multiplier = brightnessMultiplier/100.0f;
  leds[led%NUM_LEDS] = CRGB((red%256)*multiplier, (green%256)*multiplier, (blue%256)*multiplier);
  show();
}
