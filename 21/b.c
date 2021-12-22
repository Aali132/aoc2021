#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int p1_start;
int p2_start;

int split(int roll) {
  if(roll == 3) {
    return 1;
  } else if(roll == 4) {
    return 3;
  } else if(roll == 5) {
    return 6;
  } else if(roll == 6) {
    return 7;
  } else if(roll == 7) {
    return 6;
  } else if(roll == 8) {
    return 3;
  } else if(roll == 9) {
    return 1;
  }
  
  return -1;
}

int64_t univ[21][10][21][10];

int64_t next_univ[21][10][21][10];

int p1p2;

int aoc(FILE *input) {
  fscanf(input, "Player 1 starting position: %i\n", &p1_start);
  fscanf(input, "Player 2 starting position: %i\n", &p2_start);
  
  univ[0][p1_start - 1][0][p2_start - 1] = 1;
  
  int64_t total_univ = 1;
  int64_t won1 = 0;
  int64_t won2 = 0;
  
  while(total_univ > won1 + won2) {
    memset(next_univ, 0, sizeof(next_univ));
    
    p1p2 = !p1p2;
    
    for(int p1s = 0; p1s < 21; p1s++) {
      for(int p1p = 0; p1p < 10; p1p++) {
        for(int p2s = 0; p2s < 21; p2s++) {
          for(int p2p = 0; p2p < 10; p2p++) {
            int64_t prev = univ[p1s][p1p][p2s][p2p];
            
            if(prev) {
              total_univ -= prev;
              
              if(p1p2) {
                for(int r = 3; r < 10; r++) {
                  int newpos = (p1p + r) % 10;
                  int newscore = p1s + newpos + 1;
                  int64_t next = prev * split(r);
                  
                  total_univ += next;
                  
                  if(newscore >= 21) {
                    won1 += next;
                  } else {
                    next_univ[newscore][newpos][p2s][p2p] += next;
                  }
                }
              } else {
                for(int r = 3; r < 10; r++) {
                  int newpos = (p2p + r) % 10;
                  int newscore = p2s + newpos + 1;
                  int64_t next = prev * split(r);
                  
                  total_univ += next;
                  
                  if(newscore >= 21) {
                    won2 += next;
                  } else {
                    next_univ[p1s][p1p][newscore][newpos] += next;
                  }
                }
              }
            }
          }
        }
      }
    }
    
    memcpy(univ, next_univ, sizeof(univ));
  }
  
  printf("%li\n", won1 > won2 ? won1 : won2);

  return 0;
}
