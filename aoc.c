#include <stdio.h>

int aoc(FILE *input);

int main(int argc, char *argv[]) {
  if(argc < 2) {
    printf("usage: %s <input file>\n", argv[0]);
    return -1;
  }

  FILE *f = fopen(argv[1], "rb");
  
  return aoc(f);
}
