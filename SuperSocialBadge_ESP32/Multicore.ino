void MultiCore( void * pvParameters ) {
  Serial.println("Procesos en Procesador 0 Iniciados");
  InicializarPantallas();
  IniciarNeoPixel();
  MostarNumero(23456, CantidadDisplay);
  delay(1000);
  while (true) {
    //while (true) {
    for (int i = 0; i < 5;  i++) {
      Serial.print(digitalRead(Botones[i]));
      Serial.print(" -  ");
    }
    Serial.println();
    delay(100);
  }


  MostarNumero(23456, CantidadDisplay);
  delay(200);
  colorWipe(Rojo, 50);
  ActualizarNeoPixel();
  // }

  switch (Modo) {
    case Menu:

      break;
    case Social:
      switch (EstadoPantalla) {
        case 0:
          Serial.println("Esperando Wifi");
          colorWipe(Rojo, 50);
          break;
        case 1:
          Serial.println("Esperando RedesSociales");
          MostarNumero( 0, CantidadDisplay);
          colorWipe(Azul, 50);
          break;
        case 2:
          Serial.println("---Datos----");
          colorWipe(Blanco, 50); // Red
          EstadoPantalla = 3;
          break;
        case 3:
          CambiarDisplay();
          break;
        default:
          Serial.println("Habla con chepecarlos tenemos un problema");
          break;
      }
      break;
    case App:

      break;
    case Rastreo:
      if (GPSActivo) {
        digitalWrite(LedIndicador, 0);
        delay(50);
        digitalWrite(LedIndicador, 1);
        delay(50);
      }
      else {
        digitalWrite(LedIndicador, 0);
        delay(500);
        digitalWrite(LedIndicador, 1);
        delay(500);
      }
      break;
  }
  ActualizarNeoPixel();
  delay(10);
}


void CambiarDisplay() {
  if (millis() > SiquienteCambioDisplay) {
    Mostar =  SiquienteRed(Mostar) ;
    MostarNumero(Sub[Mostar], CantidadDisplay);//Muestra el numero de Segidores
    SiquienteCambioDisplay = millis() + EsperaCambioDisplay;
  }
}


int SiquienteRed(int Actual) {
  Serial.println();
  while (true) {
    Actual++;
    if (Actual > 2 )
      Actual = 0;

#ifdef FacebookID
    if (Actual == Facebook) {
      Serial.print("Facebook ");
      return Actual;
    }
#endif

#ifdef InstagramID
    if (Actual == Instagram) {
      Serial.print("Instagram ");
      return Actual;
    }
#endif

#ifdef YoutubeID
    if (Actual == Youtube) {
      Serial.print("Youtube ");
      return Actual;
    }
#endif
  }
}
