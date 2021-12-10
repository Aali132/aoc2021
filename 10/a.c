#include <stdio.h>
#include <string.h>

char chunks[4096];

int aoc(FILE *input) {
  char line[4096];
  int score = 0;
  
  while(fgets(line, sizeof(line), input)) {
    int len = strlen(line);
    int chunk_index = 0;
    
    for(int i = 0; i < len; i++) {
      if(line[i] == '(') {
        chunks[chunk_index++] = line[i];
      }
      if(line[i] == '[') {
        chunks[chunk_index++] = line[i];
      }
      if(line[i] == '{') {
        chunks[chunk_index++] = line[i];
      }
      if(line[i] == '<') {
        chunks[chunk_index++] = line[i];
      }
      if(line[i] == ')') {
        if(chunks[chunk_index - 1] == '(') {
          chunk_index--;
        } else {
          score += 3;
          break;
        }
      }
      if(line[i] == ']') {
        if(chunks[chunk_index - 1] == '[') {
          chunk_index--;
        } else {
          score += 57;
          break;
        }
      }
      if(line[i] == '}') {
        if(chunks[chunk_index - 1] == '{') {
          chunk_index--;
        } else {
          score += 1197;
          break;
        }
      }
      if(line[i] == '>') {
        if(chunks[chunk_index - 1] == '<') {
          chunk_index--;
        } else {
          score += 25137;
          break;
        }
      }
    }
  }
  
  printf("%i\n", score);

  return 0;
}
