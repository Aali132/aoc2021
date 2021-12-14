#include <stdio.h>
#include <string.h>
#include <limits.h>

char seq[1024];

struct {
  unsigned char pattern[2];
  unsigned char insert;
} rules[256];

int num_rules;

int64_t pairs[256][256];
int64_t new_pairs[256][256];

int aoc(FILE *input) {
  fgets(seq, sizeof(seq), input);
  
  strtok(seq, "\r\n");
  
  for(int i = 1; i < strlen(seq); i++) {
    pairs[(unsigned char)seq[i - 1]][(unsigned char)seq[i]]++;
  }
  
  char line[128];
  
  fgets(line, sizeof(line), input);
  
  while(fgets(line, sizeof(line), input)) {
    rules[num_rules].pattern[0] = line[0];
    rules[num_rules].pattern[1] = line[1];
    rules[num_rules].insert = line[6];
    
    num_rules++;
  }
  
  for(int step = 0; step < 40; step++) {
    for(int r = 0; r < num_rules; r++) {
      int64_t matching_pairs = pairs[rules[r].pattern[0]][rules[r].pattern[1]];
      
      new_pairs[rules[r].pattern[0]][rules[r].insert] += matching_pairs;
      new_pairs[rules[r].insert][rules[r].pattern[1]] += matching_pairs;
    }
    
    memcpy(pairs, new_pairs, sizeof(pairs));
    memset(new_pairs, 0, sizeof(new_pairs));
  }
  
  pairs[(unsigned char)seq[strlen(seq) - 1]][0]++;
  
  int64_t min = LLONG_MAX;
  int64_t max = 0;
  
  for(int i = 0; i < 256; i++) {
    int64_t count = 0;
    
    for(int j = 0; j < 256; j++) {
      count += pairs[i][j];
    }
    
    if(count && count < min) {
      min = count;
    }
    
    if(count > max) {
      max = count;
    }
  }
  
  printf("%li\n", max - min);

  return 0;
}
