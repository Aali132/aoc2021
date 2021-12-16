#include <stdio.h>
#include <string.h>

int grid[1024][1024];
int width;
int height;

int cost[1024][1024];

int calc_cost(int x, int y) {
  if(x == 0 && y == 0) {
    return 0;
  }
  
  if(x == 0) {
    return cost[y - 1][x] + grid[y][x];
  }
  
  if(y == 0) {
    return cost[y][x - 1] + grid[y][x];
  }
  
  int costx = cost[y][x - 1] + grid[y][x];
  int costy = cost[y - 1][x] + grid[y][x];
  
  return costx < costy ? costx : costy;
}

int aoc(FILE *input) {
  char line[1024];
  
  while(fgets(line, sizeof(line), input)) {
    strtok(line, "\r\n");
    
    if(!width) {
      width = strlen(line);
    }
    
    for(int i = 0; i < width; i++) {
      grid[height][i] = line[i] - '0';
    }
    
    height++;
  }
  
  for(int row = 0; row < height; row++) {
    for(int col = 0; col < width; col++) {
      for(int y = row; y < height; y++) {
        cost[y][col] = calc_cost(col, y);
      }
      
      for(int x = col; x < width; x++) {
        cost[row][x] = calc_cost(x, row);
      }
    }
  }
  
  printf("%i\n", cost[height - 1][width - 1]);
  
  return 0;
}
