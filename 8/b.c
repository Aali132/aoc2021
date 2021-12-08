#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int intersect(char *a, char *b) {
  int result = 0;
  
  do {
    if(strchr(b, *a)) {
      result++;
    }
  } while(*++a);
  
  return result;
}

int aoc(FILE *input) {
  char line[4096];
  int sum = 0;
  
  while(fgets(line, sizeof(line), input)) {
    char *seq[10];
    int digit[10];
    
    memset(digit, -1, sizeof(digit));
    
    strtok(line, "\r\n");
    
    char *pattern = strtok(line, " ");
    int seq_count = 0;
    
    while(pattern) {
      if(!strcmp(pattern, "|")) {
        break;
      }
      
      int len = strlen(pattern);
      
      if(len == 2) {
        digit[1] = seq_count;
      } else if(len == 3) {
        digit[7] = seq_count;
      } else if(len == 4) {
        digit[4] = seq_count;
      } else if(len == 7) {
        digit[8] = seq_count;
      }
      
      seq[seq_count++] = pattern;
      
      pattern = strtok(0, " ");
    }
    
    for(int i = 0; i < 10; i++) {
      int len = strlen(seq[i]);
      int i1 = intersect(seq[digit[1]], seq[i]);
      int i4 = intersect(seq[digit[4]], seq[i]);
      
      if(len == 6) {
        if(i4 == 4) {
          digit[9] = i;
        } else if(i1 == 1) {
          digit[6] = i;
        } else {
          digit[0] = i;
        }
      }
      
      if(len == 5) {
        if(i1 == 2) {
          digit[3] = i;
        } else if(i4 == 2) {
          digit[2] = i;
        } else {
          digit[5] = i;
        }
      }
    }
    
    char number[128];
    int pos = 0;
    
    pattern = strtok(0, " ");
    
    while(pattern) {
      for(int i = 0; i < 10; i++) {
        char *s = seq[digit[i]];
        
        if(strlen(s) == strlen(pattern) && intersect(s, pattern) == strlen(s)) {
          number[pos++] = '0' + i;
          break;
        }
      }
      
      pattern = strtok(0, " ");
    }
    
    number[pos] = 0;
    
    sum += atoi(number);
  }
  
  printf("%i\n", sum);

  return 0;
}
