#include <stdio.h>

int triangular(int n) {
  return n * (n + 1) / 2;
}

int xmin, xmax, ymin, ymax;

int count_hits() {
  int result = 0;
  
  for(int x = 0; x < 500; x++) {
    for(int y = -200; y < 200; y++) {
      for(int n = 1; n < 300; n++) {
        int xpos = triangular(x) - triangular(x - n);
        int ypos = triangular(y) - triangular(y - n);
        
        if(x - n < 0) {
          xpos = triangular(x);
        }
        
        if(xpos <= xmax && xpos >= xmin && ypos <= ymax && ypos >= ymin) {
          result++;
          break;
        }
        
        if(ypos < ymin) {
          break;
        }
      }
    }
  }
  
  return result;
}

int aoc(FILE *input) {
  fscanf(input, "target area: x=%i..%i, y=%i..%i", &xmin, &xmax, &ymin, &ymax);
  
  int count = count_hits();
  
  printf("%i\n", count);

  return 0;
}
