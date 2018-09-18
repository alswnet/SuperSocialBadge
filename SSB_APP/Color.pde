
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
