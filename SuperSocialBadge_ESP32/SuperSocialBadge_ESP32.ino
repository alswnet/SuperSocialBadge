#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h> //Libreria de Consultas Escriptadas
#include "Contrasenna.h"//Archivo con info de contrasenas para hacer las consultas
#include <ArduinoJson.h>//Libreria de Decifrado Json
#include "JsonStreamingParser.h"///Libreria de Decifrado Json

//ID de Redes Sociales
#define InstagramID "alswnet"//usuario ALSW de Insgramam 
#define FacebookID "163069780414846"//ID ALSW de fanpage de Facebook
#define YoutubeID "UCS5yb75qx5GFOG-uV5JLYlQ" // ID ALSW de Canal de Youtube

#define Facebook 0
#define Youtube 1
#define Instagram 2

#define Menu 0
#define Social 1
#define App 2
#define GPS 3

#define Negro 0
#define Blanco 1
#define Rojo 2
#define Azul 3
#define Verde 4

WiFiMulti wifiMulti;
WiFiClientSecure client;

unsigned long SiquientePreguntaAPI = 0;
unsigned long SiquienteCambioDisplay = 0;
unsigned long TiempoActual = 0;

const unsigned long ValocidadBarrido = 300;
const unsigned long EsperaEstreConsulta = 1000;//cada n/1000 segundos
const unsigned long EsperaCambioDisplay = 10000;//cada n/1000 Segundo
const unsigned int LedIndicador = 5;
const unsigned int Boton = 0;
const unsigned int CantidadDisplay = 4;
const unsigned int CantidadLado = 16;

unsigned int Mostar = 1;
unsigned int Estado = 0;
unsigned int Modo = App;
unsigned int Sub[3] = {0, 0, 0};
unsigned int SubAnterior[3] = {0, 0, 0};

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
  IniciarNeoPizel();
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
    //  rainbow(20);
    //  colorWipe(strip.Color(0, 0, 0), 50); // Red
   //   strip.show();
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

