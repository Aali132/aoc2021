#include <stdio.h>
#include <string.h>

int lut[512];

int image[256][256];
int width;
int height;

int get_pixel(int x, int y, int depth) {
  if(depth == 0) {
    if(x < -width / 2 || x > width / 2 || y < -height / 2 || y > height / 2) {
      return 0;
    }
    
    return image[y + height / 2][x + width / 2];
  } else {
    int lookup = 0;
    
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
        lookup = (lookup << 1) | get_pixel(x + j - 1, y + i - 1, depth - 1);
      }
    }
    
    return lut[lookup];
  }
}

int aoc(FILE *input) {
  char line[1024];
  
  fgets(line, sizeof(line), input);
  
  for(int i = 0; i < 512; i++) {
    lut[i] = line[i] == '#';
  }
  
  fgets(line, sizeof(line), input);
  
  while(fgets(line, sizeof(line), input)) {
    if(!width) {
      width = strlen(line) - 1;
    }
    
    for(int i = 0; i < width; i++) {
      image[height][i] = line[i] == '#';
    }
    
    height++;
  }
  
  int lit_pixels = 0;
  
  for(int y = -100; y < 100; y++) {
    for(int x = -100; x < 100; x++) {
      lit_pixels += get_pixel(x, y, 2);
    }
  }
  
  printf("%i\n", lit_pixels);

  return 0;
}
