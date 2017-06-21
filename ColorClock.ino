#include <Adafruit_NeoPixel.h>
#define PIN 9
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);
int rgb[3];
int r = 0;
int g = 0;
int b = 0;
boolean c = 0;
int tol = 125; //Tolerance for how much the color should change each cycle
int wtol = 200; //Tolerance for how close a color can be to white
void setup()
{
  // Serial.begin(9600);
  strip.begin();
  strip.setBrightness(255);
  strip.show();
  randomSeed(analogRead(0)); //Randomize seed by reading pin 0
}

void loop()
{
  wipeRandom(3750); //60 seconds / 16 pixels = 3750 ms per pixel
}

//Randomize color and fill, wait defines time per pixel
void wipeRandom(int wait)
{
  c = 0;
  while (c == 0)
  {
    rgb[0] = random(0, 255);
    rgb[1] = random(0, 255);
    rgb[2] = random(0, 255);
    if ((abs(rgb[0] - r) + abs(rgb[1] - g) + abs(rgb[2] - b)) > tol)
    {
      c = 1; // Make sure color changes
      if (abs(rgb[0] - rgb[1]) < wtol && abs(rgb[0] - rgb[2]) < wtol && abs(rgb[1] - rgb[2]) < wtol)
      {
        c = 0; // Avoid whites
      }
    }
  }
  // Serial.print(rgb[0]);
  // Serial.print("  ");
  // Serial.print(rgb[1]);
  // Serial.print("  ");
  // Serial.println(rgb[2]);
  colorWipe(rgb, wait);
  r = rgb[0];
  g = rgb[1];
  b = rgb[2]; //save values to compare in next loop
}

// Fill the dots one after the other with a color
void colorWipe(int rgb[3], int wait)
{
  // for(int i = 0; i < strip.numPixels(); i++){
  // strip.setPixelColor(i, 0); //clear
  // }
  // for(uint16_t i=0; i<strip.numPixels(); i++) {
  // strip.setPixelColor(i, c);
  // strip.show();
  // delay(wait);
  // fillPixel(25, wait, i);
  // }
  double steps = 75.0;
  for (int i = 7; i >= 0; i--)
  {
    fillPixel(steps, wait, i, rgb); //First strip
  }
  for (int i = 15; i >= 8; i--)
  {
    fillPixel(steps, wait, i, rgb); //Second strip
  }
}

//Transitions one pixel gradually
void fillPixel(double steps, int wait, int pixel, int rgb[3])
{
  for (double i = 1.0; i <= steps; i++)
  {
    strip.setPixelColor(pixel,(r - ((r - rgb[0]) * (i/steps))),(g - ((g - rgb[1]) * (i/steps))),(b - ((b - rgb[2]) * (i/steps))));
    // Serial.println((r - ((r - rgb[0]) * (i/steps))));
    strip.show();
    delay(wait / steps);
  }
  // Serial.print("---> ");
  // Serial.print(r);
  // Serial.print("  ");
  // Serial.println(rgb[0]);
}

// Old example functions
// void rainbow(uint8_t wait)
// {
//   uint16_t i, j;
//   for (j = 0; j < 256; j++)
//   {
//     for (i = 0; i < strip.numPixels(); i++)
//     {
//       strip.setPixelColor(i, Wheel((i + j) & 255));
//     }
//     strip.show();
//     delay(wait);
//   }
// }

// // Slightly different, this makes the rainbow equally distributed throughout
// void rainbowCycle(uint8_t wait)
// {
//   uint16_t i, j;
//   for (j = 0; j < 256 * 5; j++)
//   {
//     // 5 cycles of all colors on wheel
//     for (i = 0; i < strip.numPixels(); i++)
//     {
//       strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
//     }
//     strip.show();
//     delay(wait);
//   }
// }

// // Theatre-style crawling lights.
// void theaterChase(uint32_t c, uint8_t wait)
// {
//   for (int j = 0; j < 10; j++)
//   {
//     // do 10 cycles of chasing
//     for (int q = 0; q < 3; q++)
//     {
//       for (int i = 0; i < strip.numPixels(); i = i + 3)
//       {
//         strip.setPixelColor(i + q, c); // turn every third pixel on
//       }
//       strip.show();
//       delay(wait);
//       for (int i = 0; i < strip.numPixels(); i = i + 3)
//       {
//         strip.setPixelColor(i + q, 0); // turn every third pixel off
//       }
//     }
//   }
// }

// // Theatre-style crawling lights with rainbow effect
// void theaterChaseRainbow(uint8_t wait)
// {
//   for (int j = 0; j < 256; j++)
//   {
//     // cycle all 256 colors in the wheel
//     for (int q = 0; q < 3; q++)
//     {
//       for (int i = 0; i < strip.numPixels(); i = i + 3)
//       {
//         strip.setPixelColor(i + q, Wheel((i + j) % 255)); // turn every third pixel on
//       }
//       strip.show();
//       delay(wait);
//       for (int i = 0; i < strip.numPixels(); i = i + 3)
//       {
//         strip.setPixelColor(i + q, 0); // turn every third pixel off
//       }
//     }
//   }
// }

// // Input a value 0 to 255 to get a color value.
// // The colours are a transition r - g - b - back to r.
// uint32_t Wheel(byte WheelPos)
// {
//   if (WheelPos < 85)
//   {
//     return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//   }
//   else
//     if (WheelPos < 170)
//     {
//       WheelPos -= 85;
//       return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//     }
//   else
//   {
//     WheelPos -= 170;
//     return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//   }
// }
