#include <stdio.h>

int p1_start;
int p2_start;

int p1_score;
int p2_score;

int rolls;

int roll_dice() {
  static int dice;
  
  rolls++;
  
  return (dice++ % 100) + 1;
}

int p1p2;

int aoc(FILE *input) {
  fscanf(input, "Player 1 starting position: %i\n", &p1_start);
  fscanf(input, "Player 2 starting position: %i\n", &p2_start);
  
  while(p1_score < 1000 && p2_score < 1000) {
    if(!p1p2) {
      p1_start = ((p1_start + roll_dice() + roll_dice() + roll_dice() - 1) % 10) + 1;
      
      p1_score += p1_start;
    } else {
      p2_start = ((p2_start + roll_dice() + roll_dice() + roll_dice() - 1) % 10) + 1;
      
      p2_score += p2_start;
    }
    
    p1p2 = !p1p2;
  }
  
  if(p1_score >= 1000) {
    printf("%i\n", rolls * p2_score);
  } else {
    printf("%i\n", rolls * p1_score);
  }

  return 0;
}
