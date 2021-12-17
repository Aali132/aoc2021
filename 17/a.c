#include <stdio.h>

int triangular(int n) {
  return n * (n + 1) / 2;
}

int xmin, xmax, ymin, ymax;

int calc_y() {
  int result = -1;
  
  for(int y = 0; y < 200; y++) {
    for(int n = 1; n < 100; n++) {
      int pos = -(triangular(y + n) - triangular(y));
      
      if(pos <= ymax && pos >= ymin) {
        result = y;
      } else {
        break;
      }
    }
  }
  
  return result;
}

int aoc(FILE *input) {
  fscanf(input, "target area: x=%i..%i, y=%i..%i", &xmin, &xmax, &ymin, &ymax);
  
  int y = calc_y();
  
  printf("%i\n", triangular(y));

  return 0;
}
