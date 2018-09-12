//Configuraciones de RED
char ssid3[] = "G_WIFI"; //Nombre de Red 1
char password3[] = "Medicina09";  //Contrasenna de Red 1
char ssid2[] = "ALSW"; //Nombre de Red 2
char password2[] = "2526-4897";  //Contrasenna de Red 2
char ssid1[] = "ALSW2"; //Nombre de Red 1
char password1[] = "7210-3607";  //Contrasenna de Red 1

void ConectarWifi() {

  wifiMulti.addAP(ssid1, password1);
  wifiMulti.addAP(ssid2, password2);
  wifiMulti.addAP(ssid3, password3);

  Serial.println("Conectando con Wifi...");
  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi Conectado");
    Serial.println("Mi IP es: ");
    Serial.println(WiFi.localIP());
  }
}

void WifiActiva() {
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi No Conectada!");
    delay(1000);
  }
}
