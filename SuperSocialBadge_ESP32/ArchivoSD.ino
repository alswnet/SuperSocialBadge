#include "FS.h"
#include "SD.h"
#include "SPI.h"

const char *ArchivoToken = "/Token.txt";

void InicializarSD() {
  if (!SD.begin(33)) {
    Serial.println("Error Cargando la SD");
    return;
  }

  uint8_t cardType = SD.cardType();

  Serial.print("Tipo de SD: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("Desconocido");
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

}

void CargarToken() {
  int EstadoBusqueda = 0;
  int Actualizar = 0;
  File file = SD.open(ArchivoToken);
  if (!file) {
    Serial.println("Error abiendo el archivo de contrasenna");
    return;
  }
  Serial.print("Empezando a procesar Token: ");
  while (file.available()) {
    char Mensaje = file.read();
    Serial.write(Mensaje);
    switch (EstadoBusqueda) {
      case 0:
        if (Mensaje == 'Y' || Mensaje == 'y') {
          EstadoBusqueda = Youtube;
          Actualizar = 1;
        }
        else if (Mensaje == 'F' || Mensaje == 'f') {
          EstadoBusqueda = Facebook;
          Actualizar = 1;
        }
        break;
      case 1:
        if (Mensaje == ',') {
          EstadoBusqueda = 2;
        }
        break;
      case 2:
        if (Mensaje == '\n') {
          EstadoBusqueda = 0;
          Actualizar = 1;
        }
        else if (Actualizar == Youtube) {
          YOUTUBE_KEY = YOUTUBE_KEY + Mensaje;
        }
        else if (Actualizar == Facebook) {
          Facebook_KEY = Facebook_KEY + Mensaje;
        }
        break;
      default:
        EstadoBusqueda = 0;
        break;
    }
  }
  Serial.println();
  Serial.print("Youtube Token: ");
  Serial.println(YOUTUBE_KEY);

  Serial.print("Facebook Token: ");
  Serial.println(Facebook_KEY);
  file.close();
}
