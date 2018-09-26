
void onKetaiListSelection(KetaiList klist) {
  //Obtiene la cadena recien seleccionada
  NombreBT = klist.getSelection();

  //Imprime el nombre de dispositivo en terminal
  print("Dispositivo seleccionado:");
  print(NombreBT);

  //Efectua la conexion bluetooth al dispositivo seleccionado
  Kbt.connectToDeviceByName(NombreBT);

  //Desaloja la lista, ya no es necesaria
  klist = null;

  for (int i = 0; i< CantidadFilas; i++) {
    for (int j = 0; j< CantidadFilas; j++) {
      PantallaBT[i][j] = 0;
      PantallaBTAnterior[i][j] = 0;
    }
  }
}

void MandadBT() {
  String Mensaje;
  if (NombreBT != null) {
    for (int f = 0; f < CantidadFilas; f++) {
      for (int c = 0; c < CantidadFilas; c++) {
        if (PantallaBTAnterior[f][c] != PantallaBT[f][c] ) {
          Mensaje = String.format("F%dC%dV%d;\n", f, c, PantallaBT[f][c]);
          println("Enviando "+Mensaje);
          Kbt.writeToDeviceName(NombreBT, Mensaje.getBytes());
          PantallaBTAnterior[f][c] = PantallaBT[f][c];
          return;
        }
      }
    }
  }
}


void ColorFull(int ColorNumero) {
  String Mensaje;
  if (NombreBT != null) {
    Mensaje = String.format("S%d;\n", ColorNumero);
    println("Enviando "+Mensaje);
    Kbt.writeToDeviceName(NombreBT, Mensaje.getBytes());
    return;
  }
}
