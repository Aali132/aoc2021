#include <stdio.h>
#include <string.h>

int bits;

int aoc(FILE *input) {
  int ones[128];
  char line[128];
  int lines = 0;

  memset(ones, 0, sizeof(ones));

  while(fgets(line, sizeof(line), input)) {
    if(!bits) {
      bits = strlen(line) - 1;
    }
    
    for(int i = 0; i < bits; i++) {
      if(line[i] == '1') {
        ones[i]++;
      }
    }

    lines++;
  }

  int gamma = 0;

  for(int i = 0; i < bits; i++) {
    if(ones[i] > lines / 2) {
      gamma |= 1 << (bits - i - 1);
    }
  }

  int epsilon = (~gamma) & ((1 << bits) - 1);

  printf("%i\n", gamma * epsilon);

  return 0;
}
