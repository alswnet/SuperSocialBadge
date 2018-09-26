#include <NeoPixelBus.h>
const uint16_t PixelCount = 256;
const uint8_t PixelPin = 25;


NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

void IniciarNeoPixel() {
  strip.Begin();
  strip.Show();
}

void ActualizarNeoPixel() {
  strip.Show();
}

void ColorPixel(int f, int c, int v) {
  if (f % 2 == 0) {
    DecoColor(f * CantidadLado + c, v);
  } else {
    DecoColor(f * CantidadLado + c, v);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < PixelCount; i++) {
      Wheel(i, (i + j) & 255);
    }
    strip.Show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
void  Wheel(int i, byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    strip.SetPixelColor(i, RgbColor(255 - WheelPos * 3, 0, WheelPos * 3));
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    strip.SetPixelColor(i, RgbColor(0, WheelPos * 3, 255 - WheelPos * 3));
  }
  WheelPos -= 170;
  strip.SetPixelColor(i, RgbColor(WheelPos * 3, 255 - WheelPos * 3, 0));
}

void DecoColor(int i, int ColorD) {
  switch (ColorD) {
    case Negro:
      strip.SetPixelColor(i, RgbColor(0, 0, 0));

      break;
    case Blanco:
      strip.SetPixelColor(i, RgbColor(IntensidadPantalla, IntensidadPantalla, IntensidadPantalla));
      break;
    case Rojo:
      strip.SetPixelColor(i, RgbColor(IntensidadPantalla, 0, 0));
      break;
    case Verde:
      strip.SetPixelColor(i, RgbColor(0, IntensidadPantalla, 0));
      break;
    case Azul:
      strip.SetPixelColor(i, RgbColor(0, 0, IntensidadPantalla));
      break;
  }
  strip.SetPixelColor(i, RgbColor(0, 0, 0));
}

// Fill the dots one after the other with a color
void colorWipe(int c, int esperar) {
  for (int i = 0; i < PixelCount; i++) {
    DecoColor(i, c);
    strip.Show();
    delay(esperar);
  }
}


