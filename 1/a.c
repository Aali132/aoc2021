#include <stdio.h>
#include <limits.h>

int aoc(FILE *input) {
  int prev = INT_MAX;
  int val;
  int increase = 0;

  while(fscanf(input, "%i", &val) == 1) {
    if(val > prev) {
      increase++;
    }

    prev = val;
  }

  printf("%i\n", increase);

  return 0;
}
