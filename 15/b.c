#include <stdio.h>
#include <string.h>
#include <limits.h>

int grid[1024 * 5][1024 * 5];
int width;
int height;

int cost[1024 * 5][1024 * 5];

int calc_grid(int x, int y) {
  int offset = x / width + y / height;
  
  return (((grid[y % height][x % width] + offset) - 1) % 9) + 1;
}

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

int min(int a, int b) {
  return a < b ? a : b;
}

int backtrack_cost(int x, int y) {
  int up = INT_MAX;
  int down = INT_MAX;
  int left = INT_MAX;
  int right = INT_MAX;
  
  if(x == 0 && y == 0) {
    return 0;
  }
  
  if(x > 0) {
    left = cost[y][x - 1] + grid[y][x];
  }
  
  if(y > 0) {
    up = cost[y - 1][x] + grid[y][x];
  }
  
  if(x < width * 5 - 1) {
    right = cost[y][x + 1] + grid[y][x];
  }
  
  if(y < height * 5 - 1) {
    down = cost[y + 1][x] + grid[y][x];
  }
  
  return min(min(min(up, down), left), right);
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
  
  for(int y = 0; y < height * 5; y++) {
    for(int x = 0; x < width * 5; x++) {
      grid[y][x] = calc_grid(x, y);
    }
  }
  
  for(int row = 0; row < height * 5; row++) {
    for(int col = 0; col < width * 5; col++) {
      for(int y = row; y < height * 5; y++) {
        cost[y][col] = calc_cost(col, y);
      }
      
      for(int x = col; x < width * 5; x++) {
        cost[row][x] = calc_cost(x, row);
      }
    }
  }
  
  for(int step = 0; step < 5; step++) {
    for(int y = 0; y < height * 5; y++) {
      for(int x = 0; x < width * 5; x++) {
        cost[y][x] = backtrack_cost(x, y);
      }
    }
  }
  
  printf("%i\n", cost[height * 5 - 1][width * 5 - 1]);
  
  return 0;
}
