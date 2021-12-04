#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int bits;

char *numbers;

void count_bits(int position, int prefix, int *ones, int *zeroes) {
  *ones = 0;
  *zeroes = 0;
  
  for(int i = 0; i < 1 << (bits - position - 1); i++) {
    *ones += numbers[prefix | (1 << (bits - position - 1)) | i];
    *zeroes += numbers[prefix | i];
  }
}

int aoc(FILE *input) {
  int ones[128];
  char line[128];
  int lines = 0;

  memset(ones, 0, sizeof(ones));

  while(fgets(line, sizeof(line), input)) {
    if(!numbers) {
      bits = strlen(line) - 1;
      
      numbers = calloc(1 << bits, 1);
    }
    
    int decimal = 0;

    for(int i = 0; i < bits; i++) {
      if(line[i] == '1') {
      	ones[i]++;
        decimal |= 1 << (bits - i - 1);
      }
    }

    numbers[decimal] = 1;

    lines++;
  }
  
  int oxygen = 0;
  int co2 = 0;
  
  int count_one, count_zero;
  
  for(int i = 0; i < bits; i++) {
    count_bits(i, oxygen, &count_one, &count_zero);
    
    if(count_one >= count_zero) {
      oxygen |= 1 << (bits - i - 1);
    }
    
    count_bits(i, co2, &count_one, &count_zero);
    
    if(count_one == 0 && count_zero == 1) {
      
    } else if((count_one < count_zero) || (count_one == 1 && count_zero == 0)) {
      co2 |= 1 << (bits - i - 1);
    }
  }
  
  printf("%i\n", oxygen * co2);

  return 0;
}
