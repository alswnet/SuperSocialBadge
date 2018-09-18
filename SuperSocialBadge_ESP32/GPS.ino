
HardwareSerial GPS(2);

int parsingState = 0;
char parseBuffer[200];
int parseBufferPtr = 0;

void Iniciargps() {
  GPS.begin(9600);
  Serial.println("Activar gps");
}
String Mensaje = "";
void Leergps() {
  Mensaje = "";
  while (GPS.available()) {
    char Letra = GPS.read();
    Mensaje = Mensaje + Letra;

    if (Letra == '\n') {

      if (Mensaje.indexOf("GPRMC") > 0 ) {
        if ( Mensaje.indexOf(",,,,,,") == -1 ) {
          AgregarAchivo("/ViajeSanMiguel.txt", Mensaje);
          GPSActivo = true;
        }
        else {
          GPSActivo = false;
        }
        Serial.print("Mensaje: ");
        Serial.println(Mensaje);

        delay(100);
      }
      return;
    }
  }
}
