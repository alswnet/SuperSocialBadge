int CantidadFilas = 16 ;
int CantidadColores = 7;
int CantidadBoton = 4;
int ColorSelecionado = 3;

int[][] PantallaBT = new int[CantidadFilas][CantidadFilas];
float AnchoCuadro;
float ColorFilas;
float AnchoFrame;
void setup() {
   fullScreen();
 // size(360, 640);
  //noStroke();
  colorMode(RGB, height, height, height);
  rectMode(CORNER);
  AnchoCuadro = float(width)/CantidadFilas;
  ColorFilas = float(width)/CantidadColores;
  AnchoFrame = float(width)/CantidadBoton;
  for (int i = 0; i< CantidadFilas; i++) {
    for (int j = 0; j< CantidadFilas; j++) {
      PantallaBT[i][j] = 1;
    }
  }
}

void draw() {
  background(50);
  MostarColores();
  MostarPantalla();
  MostarBoton();
}

void MostarBoton() {
  pushMatrix();
  pushStyle();
  translate(0, AnchoCuadro*CantidadFilas + ColorFilas*3);
  for (int i = 0; i < CantidadBoton; i++) {
    fill(200);
    rect(AnchoFrame*i, 0, AnchoFrame, AnchoFrame*0.75);
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

void ColorActual(int ColorActual) {
  if (ColorSelecionado == ColorActual ) {
    stroke(1000, 1000, 0);
    strokeWeight(10);
  } else {
    stroke(0);
    strokeWeight(5);
  }
  switch(ColorActual) {
  case 0: 
    fill(0, 0, 0);
    break;
  case 1: 
    fill(0, 0, 1000);
    break;
  case 2: 
    fill(1000, 0, 0);
    break;
  case 3: 
    fill(0, 1000, 0);
    break;
  case 4: 
    fill(1000, 400, 400);
    break;
  case 5: 
    fill(400, 200, 1000);
    break;
  case 6: 
    fill(400, 200, 000);
    break;
  case 7: 
    fill(0, 0, 500);
    break;
  case 8: 
    fill(500, 0, 0);
    break;
  case 9: 
    fill(0, 500, 0);
    break;
  case 10: 
    fill(500, 200, 200);
    break;
  case 11: 
    fill(50, 50, 200);
    break;
  case 12: 
    fill(500, 500, 500);
    break;
  case 13: 
    fill(1000, 1000, 1000);
    break;
  default:
    fill(0, 0, 0);
    break;
  }
}

void mousePressed() {
  mouseClicked();
}

void mouseDragged() {
  mouseClicked();
}

void mouseClicked() {
  for (int i = 0; i < CantidadFilas; i++) {
    for (int j = 0; j < CantidadFilas; j++) {
      if (mouseX > AnchoCuadro*i && mouseX < AnchoCuadro*(i+1) &&
        mouseY > AnchoCuadro*j && mouseY < AnchoCuadro*(j+1)) {
        PantallaBT[i][j] = ColorSelecionado;
      }
    }
  }

  for (int i = 0; i < CantidadColores; i++) {
    if (mouseX > ColorFilas*i && mouseX < ColorFilas*(i+1) &&
      mouseY > AnchoCuadro*CantidadFilas && mouseY < AnchoCuadro*CantidadFilas + ColorFilas*1.5) {
      ColorSelecionado = i;
    }
  }

  for (int i = 0; i < CantidadColores; i++) {
    if (mouseX > ColorFilas*i && mouseX < ColorFilas*(i+1) &&
      mouseY > AnchoCuadro*CantidadFilas + ColorFilas*1.5 && mouseY < AnchoCuadro*CantidadFilas + ColorFilas*3) {
      ColorSelecionado = i+CantidadColores;
    }
  }
}
