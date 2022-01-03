#include <stdio.h>
#include <string.h>

#define EMPTY 0
#define EAST 1
#define SOUTH 2

int grid[4096][4096];
int width;
int height;

int aoc(FILE *input) {
  char line[1024];
  
  while(fgets(line, sizeof(line), input)) {
    strtok(line, "\r\n");
    
    if(!width) {
      width = strlen(line);
    }
    
    for(int i = 0; i < width; i++) {
      if(line[i] == '>') {
        grid[height][i] = EAST;
      } else if(line[i] == 'v') {
        grid[height][i] = SOUTH;
      }
    }
    
    height++;
  }
  
  static int nextgrid[4096][4096];
  int moved;
  int steps = 0;
  
  do {
    moved = 0;
    
    for(int y = 0; y < height; y++) {
      for(int x = 0; x < width; x++) {
        if(grid[y][(x + 1) % width] == EMPTY && grid[y][x] == EAST) {
          nextgrid[y][x] = EMPTY;
        } else if(grid[y][(x + width - 1) % width] == EAST && grid[y][x] == EMPTY) {
          nextgrid[y][x] = EAST;
          moved++;
        } else {
          nextgrid[y][x] = grid[y][x];
        }
      }
    }
    
    memcpy(grid, nextgrid, sizeof(grid));
    
    for(int y = 0; y < height; y++) {
      for(int x = 0; x < width; x++) {
        if(grid[(y + 1) % height][x] == EMPTY && grid[y][x] == SOUTH) {
          nextgrid[y][x] = EMPTY;
        } else if(grid[(y + height - 1) % height][x] == SOUTH && grid[y][x] == EMPTY) {
          nextgrid[y][x] = SOUTH;
          moved++;
        } else {
          nextgrid[y][x] = grid[y][x];
        }
      }
    }
    
    memcpy(grid, nextgrid, sizeof(grid));
    
    steps++;
  } while(moved > 0);
  
  printf("%i\n", steps);

  return 0;
}
