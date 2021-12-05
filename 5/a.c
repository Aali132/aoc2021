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
    
    if(x1 == x2 || y1 == y2) {
      if(x1 > x2) {
        int tmp = x1;
        x1 = x2;
        x2 = tmp;
      }
      
      if(y1 > y2) {
        int tmp = y1;
        y1 = y2;
        y2 = tmp;
      }
      
      for(int x = x1; x <= x2; x++) {
        for(int y = y1; y <= y2; y++) {
          grid[x][y]++;
          
          if(grid[x][y] == 2) {
            points++;
          }
        }
      }
    }
  }
  
  printf("%i\n", points);

  return 0;
}
