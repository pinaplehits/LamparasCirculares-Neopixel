#include <Adafruit_NeoPixel.h>

#define PIN 9
#define NUMPIXELS 24

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int RGBColorLeds[][3] = {
  {0, 0, 0}, //turn cells off
  {255, 0, 0}, //red
  {0, 255, 0}, //green
  {0, 0, 255}, //blue
  {255, 0, 255}, //purple
  {0, 255, 255}, //green_blue
  {255, 255, 0}, //yellow
  {255, 255, 255}, //white
  {255, 100, 100}, //pink
  {255, 85, 0} //orange
};

const int colorPin[] = {5, 6, 7, 8};
const int brightnessPin[] = {10, 11};
const int brightnessIntensity[] = {10, 25, 45, 60, 75, 80, 110, 150, 200, 255};
const int flashColor[] = {1, 2, 3, 6, 7, 9};
const int sizeColorPin = sizeof(colorPin) / sizeof(colorPin[0]);
const int rowsRGBColorLeds = sizeof(RGBColorLeds) / sizeof(RGBColorLeds[0]);
const int sizeBrightnessIntensity = sizeof(brightnessIntensity) / sizeof(brightnessIntensity[0]);

int i;
int currentColor = 0;
int contador;
int acumulador;

void setup()
{
  pixels.begin();
  pixels.setBrightness(128);

  for (i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, 255, 255, 255);
    pixels.show();
    delay(20);
  }

  pixels.clear();
  pixels.show();

  for (i = 0; i < sizeColorPin; i++)
  {
    pinMode(colorPin[i], INPUT);
  }

  pixels.setBrightness(brightnessIntensity[0]);
}

void loop() {
  //BRIGHTNESS SELECTOR BY PIN
  if (digitalRead(brightnessPin[0]) == LOW)
  {
    if (contador <= 0)
    {
      contador = (sizeBrightnessIntensity - 1);
      pixels.setBrightness(brightnessIntensity[contador]);
      delay(150);
    }
    else
    {
      contador--;
      pixels.setBrightness(brightnessIntensity[contador]);
      delay(150);
    }
  }

  if (digitalRead(brightnessPin[1]) == LOW)
  {
    if (contador + 1 < sizeBrightnessIntensity)
    {
      contador++;
      pixels.setBrightness(brightnessIntensity[contador]);
      delay(150);
    }
    else
    {
      contador = 0;
      pixels.setBrightness(brightnessIntensity[contador]);
      delay(150);
    }
  }

  //COLOR SELECTOR BY PIN
  if (digitalRead(colorPin[0]) == LOW)
  {
    acumulador = pow(2, 0);
    currentColor += acumulador;
    acumulador = 0;
  }

  if (digitalRead(colorPin[1]) == LOW)
  {
    acumulador = pow(2, 1);
    currentColor += acumulador;
    acumulador = 0;
  }

  if (digitalRead(colorPin[2]) == LOW)
  {
    acumulador = pow(2, 2);
    currentColor += acumulador;
    acumulador = 0;
  }

  if (digitalRead(colorPin[3]) == LOW)
  {
    acumulador = pow(2, 3);
    currentColor += acumulador;
    acumulador = 0;
  }

  if (currentColor < rowsRGBColorLeds)
  {
    for (i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, RGBColorLeds[currentColor][0], RGBColorLeds[currentColor][1], RGBColorLeds[currentColor][2]);
      pixels.show();
    }
  }
  else
  {
    currentColor -= rowsRGBColorLeds;
    currentColor = flashColor[currentColor];

    for (i = 0; i < NUMPIXELS; i++)
    {
      pixels.setPixelColor(i, RGBColorLeds[currentColor][0], RGBColorLeds[currentColor][1], RGBColorLeds[currentColor][2]);
      pixels.show();
    }

    delay(400);

    pixels.clear();
    pixels.show();

    delay(400);
  }

  currentColor = 0;
}