#include <stdio.h>
#include <string.h>

int init_area[101][101][101];

int aoc(FILE *input) {
  char onoff[128];
  int x1, x2, y1, y2, z1, z2;
  
  while(fscanf(input, "%s x=%i..%i,y=%i..%i,z=%i..%i\n", onoff, &x1, &x2, &y1, &y2, &z1, &z2) == 7) {
    int on = !strcmp(onoff, "on");
    
    if(x1 >= -50 && x2 <= 50 && y1 >= -50 && y2 <= 50 && z1 >= -50 && z2 <= 50) {
      for(int x = x1; x <= x2; x++) {
        for(int y = y1; y <= y2; y++) {
          for(int z = z1; z <= z2; z++) {
            init_area[x + 50][y + 50][z + 50] = on;
          }
        }
      }
    }
  }
  
  int count = 0;
  
  for(int x = 0; x < 101; x++) {
    for(int y = 0; y < 101; y++) {
      for(int z = 0; z < 101; z++) {
        if(init_area[x][y][z]) {
          count++;
        }
      }
    }
  }
  
  printf("%i\n", count);

  return 0;
}
