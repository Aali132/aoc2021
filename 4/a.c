#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int draws[256];
int num_draws;
int current_draw;

struct {
  int numbers[5][5];
  int marks[5][5];
  int bingo_rows[5];
  int bingo_cols[5];
} boards[256];

int num_boards = 0;

int first_bingo() {
  for(; current_draw < num_draws; current_draw++) {
    for(int b = 0; b < num_boards; b++) {
      for(int x = 0; x < 5; x++) {
        for(int y = 0; y < 5; y++) {
          if(draws[current_draw] == boards[b].numbers[y][x]) {
            boards[b].marks[y][x] = 1;
            
            boards[b].bingo_rows[y]++;
            boards[b].bingo_cols[x]++;
            
            if(boards[b].bingo_rows[y] == 5 || boards[b].bingo_cols[x] == 5) {
              return b;
            }
          }
        }
      }
    }
  }
  
  return -1;
}

int aoc(FILE *input) {
  char line[4096];
  
  fgets(line, sizeof(line), input);
  
  char *draw = strtok(line, ",");
  
  while(draw) {
    draws[num_draws++] = atoi(draw);
    
    draw = strtok(0, ",");
  }
  
  int line_index = 0;
  
  while(fgets(line, sizeof(line), input)) {
    if(line_index > 0) {
      sscanf(line, "%i %i %i %i %i", &boards[num_boards].numbers[line_index - 1][0], 
                                     &boards[num_boards].numbers[line_index - 1][1], 
                                     &boards[num_boards].numbers[line_index - 1][2], 
                                     &boards[num_boards].numbers[line_index - 1][3], 
                                     &boards[num_boards].numbers[line_index - 1][4]);
      
      if(line_index == 5) {
        line_index = -1;
        num_boards++;
      }
    }
    
    line_index++;
  }
  
  int board = first_bingo();
  int unmarked_total = 0;
  
  for(int x = 0; x < 5; x++) {
    for(int y = 0; y < 5; y++) {
      if(!boards[board].marks[y][x]) {
        unmarked_total += boards[board].numbers[y][x];
      }
    }
  }
  
  printf("%i\n", unmarked_total * draws[current_draw]);

  return 0;
}
