#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define Esperando 0
#define Guardar 1
#define Columna 2
#define Fila 3
#define ColorBT 4
#define PlayBT 5
#define PintarPantalla 6


char MensajeBT[5];
int PunteroBT = 0;
int PF = -1;
int PC = -1;
int PantallaBT[16][16];

BluetoothSerial SerialBT;
int EstadoBT = 0;

void ActivarBluetooth() {
  SerialBT.begin(NombreBT);
  Serial.println("Iniciando BT");
  delay(50);
  for (int f = 0; f < CantidadLado; f++) {
    for (int c = 0; c < CantidadLado; c++) {
      PantallaBT[f][c] = 0;
    }
  }
  Serial.println();
  MostarPTBT();
}

void LeerBluetooth() {
  while (SerialBT.available()) {
    char Mensaje = SerialBT.read();
    // Serial.print(Mensaje);
    // Serial.print("-");
    // Serial.println(EstadoBT);
    switch (EstadoBT) {
      case Esperando:
        SiquienteActualizar(Mensaje);
        break;
      case Columna:
        if (Mensaje >= '0' and Mensaje <= '9') {
          MensajeBT[PunteroBT] = Mensaje;
          PunteroBT++;
          Serial.print("-");
          Serial.print(PunteroBT);
        }
        else {
          MensajeBT[PunteroBT] = 0;
          Serial.print("Mensaje");
          Serial.println(MensajeBT);
          PC = atoi(MensajeBT);
          Serial.print("PC ");
          Serial.println(PC);
          EstadoBT = Esperando;
          SiquienteActualizar(Mensaje);
        }
        break;
      case Fila:
        if (Mensaje >= '0' and Mensaje <= '9') {
          MensajeBT[PunteroBT] = Mensaje;
          PunteroBT++;
        }
        else {
          MensajeBT[PunteroBT] = 0;
          PF = atoi(MensajeBT);
          Serial.print("PF ");
          Serial.println(PF);
          EstadoBT = Esperando;
          SiquienteActualizar(Mensaje);
        }
        break;
      case ColorBT:
        if (Mensaje >= '0' and Mensaje <= '9') {
          MensajeBT[PunteroBT] = Mensaje;
          PunteroBT++;
        }
        else {
          MensajeBT[PunteroBT] = 0;
          PantallaBT[PC][PF] = atoi(MensajeBT);
          /* Serial.print("PC ");
            Serial.print(PC);
            Serial.print(" PF ");
            Serial.print(PF);
            Serial.print(" Color ");
            Serial.println( PantallaBT[PF][PC]);*/
          MostarPTBT();
          EstadoBT = Esperando;
          SiquienteActualizar(Mensaje);
        }
        break;
      case PlayBT:
        //Todo Activar Animacion
        break;
      case Guardar:
        //TODO Guardas secuencia
        if (Mensaje >= '0' and Mensaje <= '9') {
          MensajeBT[PunteroBT] = Mensaje;
          PunteroBT++;
        }
        else {
          MensajeBT[PunteroBT] = 0;
          int Frame = atoi(MensajeBT);
          if (Frame >= 0 && Frame <= 4) {
            String NombreFrame = "/frame";
            NombreFrame =  NombreFrame + Frame;
            NombreFrame =  NombreFrame + ".txt";
            Serial.print("Empezando a Escribir Archivo: ");
            Serial.print(NombreFrame);
            File ArchivoFrame = SD.open(NombreFrame, FILE_WRITE);
            if (ArchivoFrame) {
              for (int f = 0; f < CantidadLado; f++) {
                for (int c = 0; c < CantidadLado; c++) {
                  ArchivoFrame.print(PantallaBT[f][c]);
                  if (c != CantidadLado - 1) {
                    ArchivoFrame.print(",");
                  }
                }
                ArchivoFrame.print(";\n");
              }
              ArchivoFrame.close();
            }
            else {
              Serial.println("Error no existe el archivo");
            }
          }
          EstadoBT = Esperando;
          SiquienteActualizar(Mensaje);
        }
        break;
      case PintarPantalla:
        if (Mensaje >= '0' and Mensaje <= '9') {
          MensajeBT[PunteroBT] = Mensaje;
          PunteroBT++;
        } else {
          MensajeBT[PunteroBT] = 0;
          int Numero = atoi(MensajeBT);
          for (int f = 0; f < CantidadLado; f++) {
            for (int c = 0; c < CantidadLado; c++) {
              PantallaBT[f][c] = Numero;
            }
          }
          MostarPTBT();
          EstadoBT = Esperando;
          SiquienteActualizar(Mensaje);
        }
        break;
    }
  }
}

void MostarPTBT() {
  Serial.println("##############################");
  for (int f = 0; f < CantidadLado; f++) {
    for (int c = 0; c < CantidadLado; c++) {
      ColorPixel(f, c, PantallaBT[f][c]);
      if (PantallaBT[f][c] == 0) {
        Serial.print(" ");
      }
      else {
        Serial.print(PantallaBT[f][c]);
      }
    }
    Serial.println();
  }
  Serial.println("##############################");
}

void SiquienteActualizar(char Mensaje) {
  Serial.print(".");
  if (Mensaje == 'G' || Mensaje == 'g') {
    Serial.println("Guardar");
    EstadoBT = Guardar;
  }
  else if (Mensaje == 'C' || Mensaje == 'c') {
    Serial.println("Columna");
    EstadoBT = Columna;
  }
  else if (Mensaje == 'F' || Mensaje == 'f') {
    Serial.println("Fila");
    EstadoBT = Fila;
  }
  else if (Mensaje == 'V' || Mensaje == 'v') {
    Serial.println("Color");
    EstadoBT = ColorBT;
  }
  else if (Mensaje == 'P' || Mensaje == 'p' ) {
    Serial.println("PLAY");
    EstadoBT = PlayBT;
  }
  else if (Mensaje == 'S' || Mensaje == 's') {
    Serial.println("Color Solido");
    EstadoBT = PintarPantalla;
  }

  MensajeBT[0] = 0;
  PunteroBT = 0;
}
