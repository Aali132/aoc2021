#include <stdio.h>
#include <string.h>

int grid[1024][1024];

struct {
  int lowx;
  int lowy;
} basin[1024];

int basins;

int width;
int height;

int diff(int x1, int y1, int x2, int y2) {
  if(x2 < 0 || y2 < 0) {
    return -1;
  }
  
  if(x2 >= width || y2 >= height) {
    return -1;
  }
  
  if(grid[x1][y1] > grid[x2][y2]) {
    return 1;
  } else if(grid[x1][y1] < grid[x2][y2]) {
    return -1;
  } else {
    return 0;
  }
}

int basin_size(int x, int y) {
  if(x < 0 || y < 0 || x >= width || y >= height) {
    return 0;
  }
  
  if(grid[x][y] != 9) {
    grid[x][y] = 9;
    return 1 + basin_size(x + 1, y) + basin_size(x, y + 1) + basin_size(x - 1, y) + basin_size(x, y - 1);
  }
  
  return 0;
}

int aoc(FILE *input) {
  char line[4096];
  
  while(fgets(line, sizeof(line), input)) {
    if(width == 0) {
      strtok(line, "\r\n");
      
      width = strlen(line);
    }
    
    for(int i = 0; i < width; i++) {
      grid[i][height] = line[i] - '0';
    }
    
    height++;
  }
  
  int b1_size = 0;
  int b2_size = 0;
  int b3_size = 0;
  
  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      int grad = 0;
      
      grad += diff(x, y, x + 1, y);
      grad += diff(x, y, x, y + 1);
      grad += diff(x, y, x - 1, y);
      grad += diff(x, y, x, y - 1);
      
      if(grad == -4) {
        int size = basin_size(x, y);
    
        if(size > b3_size) {
          b3_size = size;
        }
        
        if(size > b2_size) {
          b3_size = b2_size;
          b2_size = size;
        }
        
        if(size > b1_size) {
          b2_size = b1_size;
          b1_size = size;
        }
      }
    }
  }
  
  printf("%i\n", b1_size * b2_size * b3_size);

  return 0;
}
