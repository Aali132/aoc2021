#include <stdio.h>

int grid[10][10];
int flashes;

void add_energy(int x, int y) {
  if(x < 0 || y < 0 || x > 9 || y > 9) {
    return;
  }
  
  grid[y][x]++;
  
  if(grid[y][x] == 10) {
    flashes++;
    
    add_energy(x - 1, y - 1);
    add_energy(x - 1, y);
    add_energy(x - 1, y + 1);
    add_energy(x, y - 1);
    
    add_energy(x, y + 1);
    add_energy(x + 1, y - 1);
    add_energy(x + 1, y);
    add_energy(x + 1, y + 1);
  }
}

int aoc(FILE *input) {
  for(int y = 0; y < 10; y++) {
    char line[128];
    
    fgets(line, sizeof(line), input);
    
    for(int x = 0; x < 10; x++) {
      grid[y][x] = line[x] - '0';
    }
  }
  
  for(int s = 0; s < 100; s++) {
    for(int y = 0; y < 10; y++) {
      for(int x = 0; x < 10; x++) {
        add_energy(x, y);
      }
    }
    
    for(int y = 0; y < 10; y++) {
      for(int x = 0; x < 10; x++) {
        if(grid[y][x] > 9) {
          grid[y][x] = 0;
        }
      }
    }
  }
  
  printf("%i\n", flashes);

  return 0;
}
