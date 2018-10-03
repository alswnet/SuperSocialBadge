
int MX = 100;

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
    fill(MX, 0, 0);
    break;
  case 2: 
    fill(0, MX, 0);
    break;
  case 3: 
    fill(0, 0, MX);
    break;
  case 4: 
    fill(MX, MX, 0);
    break;
  case 5: 
    fill(0, MX, MX);
    break;
  case 6: 
    fill(MX, 0, MX);
    break;
  case 7: 
    fill(MX, MX, MX);
    break;
  default:
    fill(0, 0, 0);
    break;
  }
}
