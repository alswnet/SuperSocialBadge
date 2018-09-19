#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define BTNombre 6
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

void AgregarAchivo(const char * path, const String message) {
  File Archivo = SD.open(path, FILE_APPEND);
  if (!Archivo) {
    Serial.println("Error con estribier archivo");
    return;
  }
  if (Archivo.print(message)) {
    Serial.print("Grabando en Archivo: ");
    Serial.println(path);
  } else {
    Serial.println("Append failed");
  }
  Archivo.close();
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
          EstadoBusqueda = 1;
          Actualizar = Youtube;
        }
        else if (Mensaje == 'F' || Mensaje == 'f') {
          EstadoBusqueda = 1;
          Actualizar = Facebook;
        }
        else if (Mensaje == 'B' || Mensaje == 'b') {
          EstadoBusqueda = 1;
          NombreBT = "";
          Actualizar = BTNombre;
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
          Actualizar = 0;
        }
        else if (Actualizar == Youtube) {
          YOUTUBE_KEY = YOUTUBE_KEY + Mensaje;
        }
        else if (Actualizar == Facebook) {
          Facebook_KEY = Facebook_KEY + Mensaje;
        }
        else if (Actualizar == BTNombre) {
          NombreBT = NombreBT + Mensaje;
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


  Serial.print("Nombre BT: ");
  Serial.println(NombreBT);
  file.close();
  delay(10000);
}

