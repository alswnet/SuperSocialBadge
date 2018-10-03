import java.util.*;
import ketai.ui.*;
import ketai.net.bluetooth.*;
import ketai.sensors.*;

KetaiBluetooth Kbt;
KetaiSensor Ksen;
ArrayList listaDisp;

String NombreBT;
int CantidadFilas = 15 ;
int CantidadColores = 7;
int CantidadBoton = 5;
int ColorSelecionado = 3;
int ColorSelecionadoAnterior = 3;
float TiempoColor = 0;

int[][] PantallaBT = new int[CantidadFilas][CantidadFilas];
int[][] PantallaBTAnterior = new int[CantidadFilas][CantidadFilas];

float AnchoCuadro;
float ColorFilas;
float AnchoFrame;

void setup() {
  fullScreen();
  orientation(PORTRAIT);    
  // size(360, 640);

  //Inicializa las clases de bluetooth y sensores
  Kbt = new KetaiBluetooth(this);
  Ksen = new KetaiSensor(this);
  Ksen.start();

  //Obtiene la lista de dispositivos bluetooth emparejados
  listaDisp = Kbt.getPairedDeviceNames();

  //Imprime la lista en terminal
  Iterator itr = listaDisp.iterator();
  println("Dispositivos emparejados:");
  while (itr.hasNext()) {
    println(itr.next());
  }

  colorMode(RGB, 100);
  rectMode(CORNER);
  AnchoCuadro = float(width)/CantidadFilas;
  ColorFilas = float(width)/CantidadColores;
  AnchoFrame = float(width)/CantidadBoton;
  for (int i = 0; i< CantidadFilas; i++) {
    for (int j = 0; j< CantidadFilas; j++) {
      PantallaBT[i][j] = 0;
      PantallaBTAnterior[i][j] = 0;
    }
  }
}

void draw() {
  background(50);
  MostarColores();
  MostarPantalla();
  MostarFrama();
  MostrarConectar();
  MandadBT();
}

void MostarFrama() {
  pushMatrix();
  pushStyle();
  translate(0, AnchoCuadro*CantidadFilas + ColorFilas*3);
  for (int i = 0; i < CantidadBoton; i++) {
    fill(200);
    rect(AnchoFrame*i, 0, AnchoFrame, AnchoFrame);
    fill(1000, 0, 0);
    textSize(30);
    text(i, AnchoFrame*i+AnchoFrame/2, AnchoFrame/2);
  }
  popStyle();
  popMatrix();
}

void MostarPantalla() {
  for (int i = 0; i< CantidadFilas; i++) {
    for (int j = 0; j< CantidadFilas; j++) {
      ColorActual(PantallaBT[i][j]);
      stroke(0);
      strokeWeight(1);
      rect(AnchoCuadro*i, AnchoCuadro*j, AnchoCuadro, AnchoCuadro);
    }
  }
}


void MostarColores() {
  pushMatrix();
  pushStyle();
  translate(0, AnchoCuadro*CantidadFilas);
  fill(200, 0, 0);

  for (int i = 0; i< CantidadColores; i++) {
    ColorActual(i);
    rect(  ColorFilas*i, 0, ColorFilas, ColorFilas*1.5);
  }
  for (int i = 0; i< CantidadColores; i++) {
    ColorActual(i+CantidadColores);
    rect(  ColorFilas*i, ColorFilas*1.5, ColorFilas, ColorFilas*1.5);
  }
  popStyle();
  popMatrix();
}

void MostrarConectar() {
  pushMatrix();
  pushStyle();
  fill(0, 1000, 0);
  translate(0, AnchoCuadro*CantidadFilas + ColorFilas*3+AnchoFrame);
  rect( 0, 0, width, height-(AnchoCuadro*CantidadFilas + ColorFilas*3+AnchoFrame) );
  fill(0);
  textSize(80);
  textAlign(CENTER, CENTER);
  text("Concectar", width/2, (height-(AnchoCuadro*CantidadFilas + ColorFilas*3+AnchoFrame))/2);
  popStyle();
  popMatrix();
}
