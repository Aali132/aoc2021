#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char line[65536];
int64_t fish[9];
int64_t newfish[9];

int aoc(FILE *input) {
  fgets(line, sizeof(line), input);

  char *timer = strtok(line, ",");

  while(timer) {
    fish[atoi(timer)]++;

    timer = strtok(0, ",");
  }

  for(int day = 0; day < 256; day++) {
    newfish[0] = fish[1];
    newfish[1] = fish[2];
    newfish[2] = fish[3];
    newfish[3] = fish[4];
    newfish[4] = fish[5];
    newfish[5] = fish[6];
    newfish[6] = fish[7] + fish[0];
    newfish[7] = fish[8];
    newfish[8] = fish[0];

    memcpy(fish, newfish, sizeof(fish));
  }

  printf("%li\n", fish[0] + fish[1] + fish[2] + fish[3] + fish[4] + fish[5] + fish[6] + fish[7] + fish[8]);

  return 0;
}
