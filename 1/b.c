#include <stdio.h>
#include <limits.h>

int aoc(FILE *input) {
  int prev1 = INT_MAX;
  int prev2 = INT_MAX;
  int prev3 = INT_MAX;
  int val;
  int increase = 0;

  while(fscanf(input, "%i", &val) == 1) {
    if(prev3 != INT_MAX) {
      if(val > prev3) {
        increase++;
      }
    }

    prev3 = prev2;
    prev2 = prev1;
    prev1 = val;
  }

  printf("%i\n", increase);

  return 0;
}
