#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int grid[2048][2048];

int dimx;
int dimy;

struct {
  int dim;
  int pos;
} folds[128];

int num_folds;

int unfold(int fold, int x, int y) {
  if(fold < 0) {
    return grid[y][x];
  }
  
  int foldx = x;
  int foldy = y;
  
  if(folds[fold].dim) {
    foldy = folds[fold].pos * 2 - y;
  } else {
    foldx = folds[fold].pos * 2 - x;
  }
  
  return unfold(fold - 1, x, y) + unfold(fold - 1, foldx, foldy);
}

int aoc(FILE *input) {
  char line[128];
  
  while(fgets(line, sizeof(line), input)) {
    if(strlen(line) < 2) {
      break;
    }
    
    int x = atoi(strtok(line, ","));
    int y = atoi(strtok(0, ","));
    
    grid[y][x] = 1;
  }
  
  char xy;
  int pos;
  
  while(fscanf(input, "fold along %c=%i\n", &xy, &pos) == 2) {
    int dim = xy == 'y' ? 1 : 0;
    
    folds[num_folds].dim = dim;
    folds[num_folds].pos = pos;
    
    if(dim == 0) {
      dimx = pos;
    } else {
      dimy = pos;
    }
    
    num_folds++;
  }
  
  printf("\n");
  
  for(int y = 0; y < dimy; y++) {
    for(int x = 0; x < dimx; x++) {
      if(unfold(num_folds - 1, x, y)) {
        printf("#");
      } else {
        printf(" ");
      }
    }
    
    printf("\n");
  }

  return 0;
}
