#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char line[1024 * 1024];
int crabs[1024];
int num_crabs;
int max_position;
int best_fuel = INT_MAX;

int aoc(FILE *input) {
  fgets(line, sizeof(line), input);

  char *position = strtok(line, ",");

  while(position) {
    int crab = atoi(position);
    
    if(crab > max_position) {
      max_position = crab;
    }
    
    crabs[num_crabs++] = crab;

    position = strtok(0, ",");
  }

  for(int p = 0; p <= max_position; p++) {
    int total_fuel = 0;
    
    for(int c = 0; c < num_crabs; c++) {
      total_fuel += abs(p - crabs[c]);
    }
    
    if(total_fuel < best_fuel) {
      best_fuel = total_fuel;
    }
  }

  printf("%i\n", best_fuel);

  return 0;
}
