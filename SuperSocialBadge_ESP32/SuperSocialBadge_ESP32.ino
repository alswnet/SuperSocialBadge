//ID de Redes Sociales
#define InstagramID "alswnet"//usuario de Insgramam
#define FacebookID "163069780414846"//ID de fanpage de Facebook
#define YoutubeID "UCS5yb75qx5GFOG-uV5JLYlQ" // ID de Canal de Youtube

#define Facebook 0
#define Youtube 1
#define Instagram 2

#define Menu 0
#define Social 1
#define App 2

#include <WiFi.h>//Libreria de ESP8266
#include <WiFiMulti.h>
#include <WiFiClientSecure.h> //Libreria de Consultas Escriptadas
#include "Contrasenna.h"//Archivo con info de contrasenas para hacer las consultas

WiFiMulti wifiMulti;
WiFiClientSecure client;

#include <ArduinoJson.h>//Libreria de Decifrado Json
#include "JsonStreamingParser.h"///Libreria de Decifrado Json
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(13, 4, NEO_GRB + NEO_KHZ800);

unsigned long EsperaEstreConsulta = 1000;//cada n/1000 segundos
unsigned long EsperaCambioDisplay = 10000;//cada n/1000 Segundo
unsigned long SiquientePreguntaAPI = 0;
unsigned long SiquienteCambioDisplay = 0;
unsigned long TiempoActual = 0;
unsigned long ValocidadBarrido = 300;

const int LedIndicador = 5;
const int Boton = 0;
const int CantidadDisplay = 4;
int Mostar = 1;
int Estado = 0;
int Modo = App;
int Sub[3] = {0, 0, 0};
int SubAnterior[3] = {0, 0, 0};

#include "BluetoothSerial.h"

void setup() {
  Serial.begin(115200);
  pinMode(LedIndicador, OUTPUT);
  pinMode(Boton, INPUT_PULLUP);

  //Activando codig a cargarse en procesador 0
  //Procesador 1 Exclusico para Wifi
  //Procesador 0 Actualizar pantalla y Botones
  xTaskCreatePinnedToCore(
    MultiCore,   /* Nombre de la funcion */
    "MultiCore", /* Nombre del proceso  */
    10000,      /* Tamano de palabra */
    NULL,       /* parametros de entrada */
    0,          /* Prioridas del proceso */
    NULL,       /* Manejo del proceso  */
    0);  /* Procesador a poner la operacion */
  delay(100);

  InicializarSD();
  CargarToken();

  switch (Modo) {
    case Menu:

      break;
    case Social:
      ConectarWifi();
      CargarSocial();
      Estado = 1;

      break;
    case App:
      ActivarBluetooth();
      break;
  }

  delay(200);

  Estado = 2;

}

void loop() {
  switch (Modo) {
    case Menu:

      break;
    case Social:
      WifiActiva();
      TiempoActual = millis();
      getSegidores();

      break;
    case App:
      LeerBluetooth();
      break;
    default:

      break;
  }
  delay(200);
}


void getSegidores() {
  boolean NuevoSegidor = false;
  if (TiempoActual > SiquientePreguntaAPI)  {
    Serial.print("Buscando.");
#ifdef FacebookID
    Serial.print(".F.");
    if (NuevoSegidor || getFacebook()) {
    }
#endif
#ifdef InstagramID
    Serial.print(".I.");
    if (NuevoSegidor || getInstagram()) {
    }
#endif
#ifdef YoutubeID
    Serial.print(".Y.");
    if (NuevoSegidor || getYoutube()) {
      rainbow(20);
      colorWipe(strip.Color(0, 0, 0), 50); // Red
      strip.show();
    }
#endif
    if (NuevoSegidor) {
      Serial.println(".Si");
    }
    else {
      Serial.println(".NO");
    }
    SiquientePreguntaAPI = TiempoActual + EsperaEstreConsulta;
  }
}


void CargarSocial() {
  //TODO Anadir cargar segidores
#ifdef FacebookID
  IniciarFacebook();
  delay(10);
#endif

#ifdef InstagramID
  getInstagram();
  delay(10);
#endif

#ifdef YoutubeID
  getYoutube();
  delay(10);
#endif

#ifdef FacebookID
  getFacebook();
  delay(10);
#endif

}

