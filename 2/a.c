#include <stdio.h>
#include <string.h>

int aoc(FILE *input) {
  char move[128];
  int amount;
  int x = 0;
  int y = 0;

  while(fscanf(input, "%s %i", move, &amount) == 2) {
    if(!strcmp(move, "forward")) {
      x += amount;
    }
    if(!strcmp(move, "down")) {
      y += amount;
    }
    if(!strcmp(move, "up")) {
      y -= amount;
    }
  }

  printf("%i\n", x * y);

  return 0;
}
