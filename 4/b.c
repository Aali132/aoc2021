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
  int won;
} boards[256];

int num_boards = 0;

void reset_bingo() {
  current_draw = 0;
  
  for(int b = 0; b < num_boards; b++) {
    memset(boards[b].marks, 0, sizeof(boards[b].marks));
    memset(boards[b].bingo_rows, 0, sizeof(boards[b].bingo_rows));
    memset(boards[b].bingo_cols, 0, sizeof(boards[b].bingo_cols));
    
    boards[b].won = 0;
  }
}

int last_bingo(int stop_at) {
  int result;
  
  for(; current_draw < num_draws; current_draw++) {
    for(int b = 0; b < num_boards; b++) {
      if(boards[b].won) {
        continue;
      }
      
      for(int x = 0; x < 5; x++) {
        for(int y = 0; y < 5; y++) {
          if(draws[current_draw] == boards[b].numbers[y][x]) {
            boards[b].marks[y][x] = 1;
            
            boards[b].bingo_rows[y]++;
            boards[b].bingo_cols[x]++;
            
            if(boards[b].bingo_rows[y] == 5 || boards[b].bingo_cols[x] == 5) {
              boards[b].won = 1;
              
              result = current_draw;
              
              if(current_draw == stop_at) {
                return b;
              }
            }
          }
        }
      }
    }
  }
  
  return result;
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
  
  int last_winning_draw = last_bingo(-1);
  
  reset_bingo();
  
  int board = last_bingo(last_winning_draw);
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
