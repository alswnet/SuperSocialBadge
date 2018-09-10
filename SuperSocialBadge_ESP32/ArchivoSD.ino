#include "FS.h"
#include "SD.h"
#include "SPI.h"

void InicializarSD() {
  if (!SD.begin()) {
    Serial.println("Error Cargando la SD");
    return;
  }
}
