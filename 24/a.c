#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OP_INP 0
#define OP_ADD 1
#define OP_MUL 2
#define OP_DIV 3
#define OP_MOD 4
#define OP_EQL 5

#define P_I 0
#define P_W 1
#define P_X 2
#define P_Y 3
#define P_Z 4

struct {
  int op;
  int p1;
  int p2;
  int imm2;
} program[1024];

int count;

struct {
  int lock_off;
  int lock_pos;
  int unlock_off;
  int unlock_pos;
} pairs[7];

int stack[100];

int64_t run() {
  int64_t w = 0;
  int64_t x = 0;
  int64_t y = 0;
  int64_t z = 0;
  int in = 0;
  int locks = 0;
  int sp = 0;
  int flag = 0;
  
  for(int i = 0; i < count; i++) {
    int64_t result;
    int64_t a;
    int64_t b;
    
    if(program[i].p1 == P_W) {
      a = w;
    } else if(program[i].p1 == P_X) {
      a = x;
    } else if(program[i].p1 == P_Y) {
      a = y;
    } else if(program[i].p1 == P_Z) {
      a = z;
    }
    
    if(program[i].p2 == P_W) {
      b = w;
    } else if(program[i].p2 == P_X) {
      b = x;
    } else if(program[i].p2 == P_Y) {
      b = y;
    } else if(program[i].p2 == P_Z) {
      b = z;
    } else if(program[i].p2 == P_I) {
      b = program[i].imm2;
    }
    
    if(program[i].op == OP_INP) {
      result = 1;
      in++;
      flag = 0;
    } else if(program[i].op == OP_ADD) {
      result = a + b;
      
      if(program[i].p1 == P_X && program[i].p2 == P_I && b <= 0) {
        pairs[stack[sp - 1]].unlock_off = b;
        pairs[stack[sp - 1]].unlock_pos = in - 1;
        sp--;
        flag = 1;
      }
      
      if(program[i - 1].op == OP_ADD && program[i].p1 == P_Y && program[i].p2 == P_I && !flag) {
        stack[sp++] = locks;
        pairs[locks].lock_off = b;
        pairs[locks].lock_pos = in - 1;
        locks++;
      }
    } else if(program[i].op == OP_MUL) {
      result = a * b;
    } else if(program[i].op == OP_DIV) {
      result = a / b;
    } else if(program[i].op == OP_MOD) {
      result = a % b;
    } else if(program[i].op == OP_EQL) {
      result = a == b;
    }
    
    if(program[i].p1 == P_W) {
      w = result;
    } else if(program[i].p1 == P_X) {
      x = result;
    } else if(program[i].p1 == P_Y) {
      y = result;
    } else if(program[i].p1 == P_Z) {
      z = result;
    }
  }
  
  return z;
}

char serial[15];

int aoc(FILE *input) {
  char line[1024];
  
  while(fgets(line, sizeof(line), input)) {
    char *op = strtok(line, " \r\n");
    char *p1 = strtok(0, " \r\n");
    char *p2 = strtok(0, " \r\n");
    
    if(!strcmp(op, "inp")) {
      program[count].op = OP_INP;
    } else if(!strcmp(op, "add")) {
      program[count].op = OP_ADD;
    } else if(!strcmp(op, "mul")) {
      program[count].op = OP_MUL;
    } else if(!strcmp(op, "div")) {
      program[count].op = OP_DIV;
    } else if(!strcmp(op, "mod")) {
      program[count].op = OP_MOD;
    } else if(!strcmp(op, "eql")) {
      program[count].op = OP_EQL;
    }
    
    if(!strcmp(p1, "w")) {
      program[count].p1 = P_W;
    } else if(!strcmp(p1, "x")) {
      program[count].p1 = P_X;
    } else if(!strcmp(p1, "y")) {
      program[count].p1 = P_Y;
    } else if(!strcmp(p1, "z")) {
      program[count].p1 = P_Z;
    } else {
      printf("p1 error\n");
      return -1;
    }
    
    if(p2) {
      if(!strcmp(p2, "w")) {
        program[count].p2 = P_W;
      } else if(!strcmp(p2, "x")) {
        program[count].p2 = P_X;
      } else if(!strcmp(p2, "y")) {
        program[count].p2 = P_Y;
      } else if(!strcmp(p2, "z")) {
        program[count].p2 = P_Z;
      } else {
        program[count].p2 = P_I;
        program[count].imm2 = atoi(p2);
      }
    }
    
    count++;
  }
  
  run();
  
  for(int i = 0; i < 7; i++) {
    if(-pairs[i].unlock_off >= pairs[i].lock_off) {
      serial[pairs[i].lock_pos] = '9';
      serial[pairs[i].unlock_pos] = '9' + pairs[i].lock_off + pairs[i].unlock_off;
    } else {
      serial[pairs[i].lock_pos] = '9' - pairs[i].lock_off - pairs[i].unlock_off;
      serial[pairs[i].unlock_pos] = '9';
    }
  }
  
  printf("%s\n", serial);

  return 0;
}
