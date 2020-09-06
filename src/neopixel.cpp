#include <Adafruit_NeoPixel.h>
#include <neopixel.h>
#include <globals.h>

// initialize the neoPixels
#define PIN            6
#define NUMPIXELS      14
Adafruit_NeoPixel neoPixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void NeoPixelSetup(void)
{
    neoPixels.setBrightness(150);
    neoPixels.begin();
}

void testLamp(void)
{
  setLamp(yellow, lampVel);
  delay(100);
  setLamp(yellow, lampAlt);
  delay(100);
  setLamp(yellow, lampTracker);
  delay(100);
  setLamp(yellow, lampRestart);
  delay(100);
  setLamp(yellow, lampProgCond);
  delay(100);
  setLamp(yellow, lampGimbalLock);
  delay(100);
  setLamp(yellow, lampTemp);
  delay(100);
  setLamp(white, lampClk);
  delay(100);
  setLamp(white, lampPosition);
  delay(100);
  setLamp(white, lampOprErr);
  delay(100);
  setLamp(white, lampKeyRelease);
  delay(100);
  setLamp(white, lampSTBY);
  delay(100);
  setLamp(white, lampNoAtt);
  delay(100);
  setLamp(white, lampUplinkActy);
  delay(100);
  
  setLamp(off, lampVel);
  delay(100);
  setLamp(off, lampAlt);
  delay(100);
  setLamp(off, lampTracker);
  delay(100);
  setLamp(off, lampRestart);
  delay(100);
  setLamp(off, lampProgCond);
  delay(100);
  setLamp(off, lampGimbalLock);
  delay(100);
  setLamp(off, lampTemp);
  delay(100);
  setLamp(off, lampClk);
  delay(100);
  setLamp(off, lampPosition);
  delay(100);
  setLamp(off, lampOprErr);
  delay(100);
  setLamp(off, lampKeyRelease);
  delay(100);
  setLamp(off, lampSTBY);
  delay(100);
  setLamp(off, lampNoAtt);
  delay(100);
  setLamp(off, lampUplinkActy);
  delay(100);
}

// this is the function that sets the Lamps witch colors
void setLamp(int color, int lampNumber)
{
    /*  green                   = 1,
        white                   = 2,
        yellow                  = 3,
        orange                  = 4,
        blue                    = 5,
        red                     = 6,
        off                     = 7
    */
    switch (color)
    {
        case green:
            // Statement(s)
            neoPixels.setPixelColor(lampNumber, neoPixels.Color(0,100,0));
            neoPixels.show();   // show the updated pixel color on the hardware
            break;
        case white:
            neoPixels.setPixelColor(lampNumber, neoPixels.Color(100,100,80));
            neoPixels.show();   // show the updated pixel color on the hardware
            break;
        case yellow:
            neoPixels.setPixelColor(lampNumber, neoPixels.Color(100,100,0));
            neoPixels.show();   // show the updated pixel color on the hardware
            break;
        case orange:
            neoPixels.setPixelColor(lampNumber, neoPixels.Color(255,165,0));
            neoPixels.show();   // show the updated pixel color on the hardware
            break;
        case blue:
            neoPixels.setPixelColor(lampNumber, neoPixels.Color(0,0,200));
            neoPixels.show();   // show the updated pixel color on the hardware
            break;
        case red:
            neoPixels.setPixelColor(lampNumber, neoPixels.Color(100,0,0));
            neoPixels.show();   // show the updated pixel color on the hardware
            break;
        case off:
            neoPixels.setPixelColor(lampNumber, neoPixels.Color(0,0,0));
            neoPixels.show();   // show the updated pixel color on the hardware
            break;
        default:
            break; // Wird nicht benötigt, wenn Statement(s) vorhanden sind
    }
}