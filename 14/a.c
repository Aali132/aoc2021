#include <stdio.h>
#include <string.h>
#include <limits.h>

char seq[1024 * 1024];
char newseq[1024 * 1024];

struct {
  char pattern[2];
  char insert;
} rules[256];

int num_rules;

int count[256];

int aoc(FILE *input) {
  fgets(seq, sizeof(seq), input);
  
  strtok(seq, "\r\n");
  
  for(int i = 0; i < strlen(seq); i++) {
    count[(unsigned char)seq[i]]++;
  }
  
  char line[128];
  
  fgets(line, sizeof(line), input);
  
  while(fgets(line, sizeof(line), input)) {
    rules[num_rules].pattern[0] = line[0];
    rules[num_rules].pattern[1] = line[1];
    rules[num_rules].insert = line[6];
    
    num_rules++;
  }
  
  for(int step = 0; step < 10; step++) {
    int len = strlen(seq);
    
    int index = 0;
    
    for(int i = 1; i < len; i++) {
      newseq[index++] = seq[i - 1];
      
      for(int r = 0; r < num_rules; r++) {
        if(rules[r].pattern[0] == seq[i - 1] && rules[r].pattern[1] == seq[i]) {
          newseq[index++] = rules[r].insert;
          count[(unsigned char)rules[r].insert]++;
        }
      }
    }
    
    newseq[index++] = seq[len - 1];
    
    memcpy(seq, newseq, index);
  }
  
  int min = INT_MAX;
  int max = 0;
  
  for(int i = 0; i < 256; i++) {
    if(count[i] && count[i] < min) {
      min = count[i];
    }
    
    if(count[i] > max) {
      max = count[i];
    }
  }
  
  printf("%i\n", max - min);

  return 0;
}
