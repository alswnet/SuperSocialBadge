#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define Esperando 0
#define Guardar 1
#define Columna 2
#define Fila 3
#define ColorBT 4

int CantidadFila = 16;
char MensajeBT[5];
int PunteroBT = 0;
int PF = -1;
int PC = -1;
int PantallaBT[16][16];

BluetoothSerial SerialBT;
int EstadoBT = 0;

void ActivarBluetooth() {
  SerialBT.begin("SSB1");
  Serial.println("Iniciando BT");
  for (int i = 0; i < CantidadFila; i++) {
    for (int j = 0; j < CantidadFila; j++) {
      PantallaBT[i][j] = 0;
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
          Estado = Esperando;
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
          Estado = Esperando;
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
          Serial.print("PC ");
          Serial.print(PC);
          Serial.print(" PF ");
          Serial.print(PF);
          Serial.print(" Color ");
          Serial.println( PantallaBT[PC][PF]);
          MostarPTBT();
          EstadoBT = Esperando;
          SiquienteActualizar(Mensaje);
        }
        break;
      case Guardar:
        //TODO Guardas secuencia
        Serial.println("Funcion de Guardas");
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
              for (int i = 0; i < CantidadFila; i++) {
                for (int j = 0; j < CantidadFila; j++) {
                  ArchivoFrame.print(PantallaBT[i][j]);
                  if (j != CantidadFila - 1) {
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
        }
        Estado = Esperando;
        //MostarPTBT();
        break;
    }
  }
}

void MostarPTBT() {
  Serial.println("##############################");
  for (int i = 0; i < CantidadFila; i++) {
    for (int j = 0; j < CantidadFila; j++) {
      if (PantallaBT[i][j] == 0) {
        Serial.print(" ");
      }
      else {
        Serial.print(PantallaBT[i][j]);
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
  MensajeBT[0] = 0;
  PunteroBT = 0;
}
