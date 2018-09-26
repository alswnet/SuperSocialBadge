

void InicializarBotones() {
  for (int i = 0; i < 5; i++) {
    pinMode(Botones[i], INPUT);
  }
}

void ActualizarBotones() {
  for (int i = 0; i < 5; i++) {
    if (digitalRead(Botones[i]) == 0) {
      EstadoBotones[i] = true;
    }
    else {
      EstadoBotones[i] = false;
    }
  }

}

void SalidasBotones() {
  if (EstadoBotones[Enter]) {
    if (EstadoBotones[Arriba]) {
      Modo = App;
      Serial.println("Cambiando a Modo BT");
      delay(100);
      ESP.restart();
    }
    else if (EstadoBotones[Abajo]  ) {
      Modo = Social;
      Serial.println("Cambiando a Modo Social ");
      delay(100);
      ESP.restart();
    }
    else if (EstadoBotones[Izquierda]) {
      IntensidadPantalla -= 10 ;
      delay(300);
    }
    else if (EstadoBotones[Derecha]) {
      IntensidadPantalla +=  10;
      delay(300);
    }
    IntensidadPantalla = constrain(IntensidadPantalla, 0, 255);
    Serial.print("Intensidad ");
    Serial.println(IntensidadPantalla);
  }
}
