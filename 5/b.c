#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int grid[1024][1024];
int points;

int aoc(FILE *input) {
  char line[128];
  
  while(fgets(line, sizeof(line), input)) {
    int x1 = atoi(strtok(line, ","));
    int y1 = atoi(strtok(0, " "));
    
    strtok(0, " ");
    
    int x2 = atoi(strtok(0, ","));
    int y2 = atoi(strtok(0, ""));
    
    int xd = 0;
    int yd = 0;
    
    if(x1 < x2) {
      xd = 1;
    }
    
    if(x1 > x2) {
      xd = -1;
    }
    
    if(y1 < y2) {
      yd = 1;
    }
    
    if(y1 > y2) {
      yd = -1;
    }
    
    int x = x1;
    int y = y1;
    
    while(1) {
      grid[x][y]++;
      
      if(grid[x][y] == 2) {
        points++;
      }
      
      x += xd;
      y += yd;
      
      if((xd > 0 && x > x2) || (xd < 0 && x < x2)) {
        break;
      }
      
      if((yd > 0 && y > y2) || (yd < 0 && y < y2)) {
        break;
      }
    }
  }
  
  printf("%i\n", points);

  return 0;
}
