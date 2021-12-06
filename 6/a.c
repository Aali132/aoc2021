#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char line[65536];
int fish[1024 * 1024];
int num_fish;

int aoc(FILE *input) {
  fgets(line, sizeof(line), input);

  char *timer = strtok(line, ",");

  while(timer) {
    fish[num_fish++] = atoi(timer);

    timer = strtok(0, ",");
  }

  for(int day = 0; day < 80; day++) {
    int old_fish = num_fish;    

    for(int i = 0; i < old_fish; i++) {
      fish[i]--;

      if(fish[i] == -1) {
        fish[i] = 6;
        fish[num_fish++] = 8;
      }
    }
  }

  printf("%i\n", num_fish);

  return 0;
}
