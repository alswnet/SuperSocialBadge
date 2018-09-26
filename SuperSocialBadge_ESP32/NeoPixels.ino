#include <Adafruit_NeoPixel.h>
int PinNeoPixel = 25;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PinNeoPixel, 256, NEO_GRB + NEO_KHZ800);

int IntensidadPantalla = 255;

void IniciarNeoPixel() {
  strip.begin();
}

void ActualizarNeoPixel() {
  strip.show();
}

void ColorPixel(int f, int c, int v) {
  if (f % 2 == 0) {
    strip.setPixelColor(f * CantidadLado +   CantidadLado - c, DecoColor(v));
  } else {
    strip.setPixelColor(f * CantidadLado + c, DecoColor(v));
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

uint32_t DecoColor(int ColorD) {
  switch (ColorD) {
    case Negro:
      return strip.Color(0, 0, 0);
      break;
    case Blanco:
      return strip.Color(IntensidadPantalla, IntensidadPantalla, IntensidadPantalla);
      break;
    case Rojo:
      return strip.Color(IntensidadPantalla, 0, 0);
      break;
    case Verde:
      return strip.Color(0, IntensidadPantalla, 0);
      break;
    case Azul:
      return strip.Color(0, 0, IntensidadPantalla);
      break;
  }
  return strip.Color(0, 0, 0);
}

// Fill the dots one after the other with a color
void colorWipe(int c, int esperar) {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, DecoColor(c));
    strip.show();
    delay(esperar);
  }
}


