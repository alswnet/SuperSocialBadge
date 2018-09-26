//TODO: dejar jugar antes de conectarse
void mousePressed() {
  PrecionarPantalla();
  PrecionarColor();
  PrecionarFrame();
  PrecionarConectar();
}

void mouseDragged() {
  PrecionarPantalla();
}

void mouseClicked() {
  PrecionarPantalla();
  PrecionarColor();
  PrecionarFrame();
  PrecionarConectar();
}

void PrecionarColor() {
  // Selecionar Color
  for (int i = 0; i < CantidadColores; i++) {
    if (mouseX > ColorFilas*i && mouseX < ColorFilas*(i+1) && mouseY > AnchoCuadro*CantidadFilas && mouseY < AnchoCuadro*CantidadFilas + ColorFilas*3) {
      if ( mouseY < AnchoCuadro*CantidadFilas + ColorFilas*1.5) {
        ColorSelecionado = i;
      } else {
        ColorSelecionado = i+CantidadColores;
      }
      if (millis() - TiempoColor < 1000 && ColorSelecionadoAnterior == ColorSelecionado) {
        for (int c = 0; c<CantidadFilas; c++) {
          for (int f = 0; f<CantidadFilas; f++) {
            PantallaBT[c][f] = ColorSelecionado;
            PantallaBTAnterior[c][f] = ColorSelecionado;
            ColorFull(ColorSelecionado);
          }
        }
      }
      ColorSelecionadoAnterior = ColorSelecionado;
      TiempoColor = millis();
    }
  }
}


void PrecionarPantalla() {
  //Clip Pantalla cuadricula
  for (int i = 0; i < CantidadFilas; i++) {
    for (int j = 0; j < CantidadFilas; j++) {
      if (mouseX > AnchoCuadro*i && mouseX < AnchoCuadro*(i+1) &&
        mouseY > AnchoCuadro*j && mouseY < AnchoCuadro*(j+1)) {
        PantallaBT[i][j] = ColorSelecionado;
      }
    }
  }
}

void PrecionarFrame() {
  for (int i = 0; i< CantidadBoton; i++) {
    if (mouseY > AnchoCuadro*CantidadFilas + ColorFilas*3 &&
      mouseY < AnchoCuadro*CantidadFilas + ColorFilas*3 +AnchoFrame*0.75) {
      if (mouseX< AnchoFrame*(i+1)) {
        println("Se preciono frame"+i);
        return;
      }
    }
  }
}

void PrecionarConectar() {
  if (mouseY > AnchoCuadro*CantidadFilas + ColorFilas*3+AnchoFrame) {
    //Crea una nueva lista de seleccion en pantalla para que el
    //usuario elija un dispositivo bluetooth
    KetaiList klist = new KetaiList(this, listaDisp);
  }
}
