#include <stdio.h>
#include <string.h>

int aoc(FILE *input) {
  char line[4096];
  int easy_digits = 0;
  
  while(fgets(line, sizeof(line), input)) {
    strtok(line, "\r\n");
    
    strtok(line, "|");
    
    char *pattern = strtok(0, " ");
    
    while(pattern) {
      int len = strlen(pattern);
      
      if(len == 2 || len == 3 || len == 4 || len == 7) {
        easy_digits++;
      }
      
      pattern = strtok(0, " ");
    }
  }
  
  printf("%i\n", easy_digits);

  return 0;
}
