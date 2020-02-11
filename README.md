
# Arduino-3pin-RGB-controller

This code lets you use your Arduino for controlling a 3 pin addressable LED strip, originally designed to work with an RGB computer fan where the strip is a ring.

**Configuration**

Set this to the digital pin the RGB strip is connected to

    #define   LED_PIN        3

Set this to the number of LEDs on the RGB strip

    #define   NUM_LEDS       15

Set this to a number between 0 and 100 to set a brightness

    #define   BRIGHTNESS     100

**Setting up custom lighting mode**

You enable a lighting mode by uncommenting its function call (removing the '`//`' in front of it).
Only 1 animation mode can be enabled, less or more will break the controller.
Each lighting mode has different parameters, follow the examples.
You can use predefined colours ; `WHITE, BLACK, RED, GREEN, TURQUOISE, YELLOW, PURPLE`,
or you can use custom colours by defining Red, Green and Blue values from 0 to 255, follow the examples provided.
Where applicable, the animation speeds are `SLOWEST, SLOWER, SLOW, MEDIUM, FAST, FASTER` and `FASTEST`.
Where applicable, the animation directions are `FORWARD` and `BACKWARD`.

**Examples**
Solid colour with no animation, using one of the predefined colours

    solidColour(RED);

Solid colour with no animation, using one of the custom colour

    solidColour(0, 120, 255);

One colour pulsing fast

    pulse(TURQUOISE, FAST);
Fading from white to turquoise and back at a medium speed

    fadeTwoColours(WHITE, TURQUOISE, MEDIUM);

Two custom colours chasing each other slowly clockwise (forward)

    circleTwoColours(0,0,255, 100,0,150, SLOW, FORWARD);

Entire strip cycling through colours of rainbow as once

    solidRainbow(FAST);

Colours of rainbow going around at medium speed clockwise (forward)

    circleRainbow(MEDIUM, FORWARD);

Some colours, but not standard rainbow going around at medium speed counter clockwise (backward)

    circleRainbow2(MEDIUM, BACKWARD);
