#include <stdio.h>
#include <string.h>

char chunks[4096];
int64_t line_scores[4096];
int num_lines;
int diff[4096];

int aoc(FILE *input) {
  char line[4096];
  
  while(fgets(line, sizeof(line), input)) {
    int len = strlen(line);
    int chunk_index = 0;
    
    int corrupt = 0;
    
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
          corrupt = 1;
        }
      }
      if(line[i] == ']') {
        if(chunks[chunk_index - 1] == '[') {
          chunk_index--;
        } else {
          corrupt = 1;
        }
      }
      if(line[i] == '}') {
        if(chunks[chunk_index - 1] == '{') {
          chunk_index--;
        } else {
          corrupt = 1;
        }
      }
      if(line[i] == '>') {
        if(chunks[chunk_index - 1] == '<') {
          chunk_index--;
        } else {
          corrupt = 1;
        }
      }
    }
    
    if(!corrupt) {
      int64_t score = 0;
      
      for(int i = chunk_index - 1; i >= 0; i--) {
        if(chunks[i] == '(') {
          score = score * 5 + 1;
        }
        
        if(chunks[i] == '[') {
          score = score * 5 + 2;
        }
        
        if(chunks[i] == '{') {
          score = score * 5 + 3;
        }
        
        if(chunks[i] == '<') {
          score = score * 5 + 4;
        }
      }
      
      line_scores[num_lines++] = score;
    }
  }
  
  for(int i = 0; i < num_lines; i++) {
    for(int j = 0; j < num_lines; j++) {
      if(line_scores[i] > line_scores[j]) {
        diff[i] += 1;
        diff[j] -= 1;
      }
    }
  }
  
  for(int i = 0; i < num_lines; i++) {
    if(diff[i] == 0) {
      printf("%li\n", line_scores[i]);
      return 0;
    }
  }

  return -1;
}
