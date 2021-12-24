#include <stdio.h>
#include <limits.h>

struct state_t {
  int cost;
  int pods[16];
};

uint32_t cost(struct state_t state) {
  return state.cost;
}

struct state_t add(struct state_t state, uint32_t c) {
  state.cost += c;
  
  return state;
}

int get(struct state_t state, int pod) {
  return state.pods[pod];
}

struct state_t set(struct state_t state, int pod, int pos) {
  state.pods[pod] = pos;
  
  return state;
}

uint32_t occupied(struct state_t state) {
  uint32_t result = 0;
  
  for(int i = 0; i < 16; i++) {
    result |= 1 << get(state, i);
  }
  
  return result;
}

int open(uint32_t occu, int pos) {
  return !(occu & (1 << pos));
}

int done(struct state_t state) {
  for(int i = 0; i < 16; i++) {
    if(get(state, i) != i + 8) {
      return 0;
    }
  }
  
  return 1;
}

struct state_t move(struct state_t state, int pod, int pos, int c) {
  if(pod >= 4) {
    c *= 10;
  }
  
  if(pod >= 8) {
    c *= 10;
  }
  
  if(pod >= 12) {
    c *= 10;
  }
  
  return add(set(state, pod, pos), c);
}

int path(int from, int to, uint32_t occu) {
  if(from == to) {
    return 0;
  }
  
#define PATH(F, MIN, MAX, C, T) if(from == (F) && to >= (MIN) && to <= (MAX) && open(occu, (T))) { int pc = path((T), to, occu); if(pc != -1) { return (C) + pc; } else { return -1; } }

  PATH(0x1, 0x1, 0x17, 1, 0x2);
  
  PATH(0x2, 0x1, 0x1, 1, 0x1);
  PATH(0x2, 0x3, 0x7, 2, 0x3);
  PATH(0x2, 0x8, 0xB, 2, 0x8);
  PATH(0x2, 0xC, 0x17, 2, 0x3);
  
  PATH(0x3, 0x1, 0x2, 2, 0x2);
  PATH(0x3, 0x4, 0x7, 2, 0x4);
  PATH(0x3, 0x8, 0xB, 2, 0x8);
  PATH(0x3, 0xC, 0xF, 2, 0xC);
  PATH(0x3, 0x10, 0x17, 2, 0x4);

  PATH(0x4, 0x1, 0x3, 2, 0x3);
  PATH(0x4, 0x5, 0x7, 2, 0x5);
  PATH(0x4, 0x8, 0xB, 2, 0x3);
  PATH(0x4, 0xC, 0xF, 2, 0xC);
  PATH(0x4, 0x10, 0x13, 2, 0x10);
  PATH(0x4, 0x14, 0x17, 2, 0x5);
  
  PATH(0x5, 0x1, 0x4, 2, 0x4);
  PATH(0x5, 0x6, 0x7, 2, 0x6);
  PATH(0x5, 0x8, 0xF, 2, 0x4);
  PATH(0x5, 0x10, 0x13, 2, 0x10);
  PATH(0x5, 0x14, 0x17, 2, 0x14);
  
  PATH(0x6, 0x1, 0x5, 2, 0x5);
  PATH(0x6, 0x7, 0x7, 1, 0x7);
  PATH(0x6, 0x8, 0x13, 2, 0x5);
  PATH(0x6, 0x14, 0x17, 2, 0x14);
  
  PATH(0x7, 0x1, 0x17, 1, 0x6);
  
  PATH(0x8, 0x1, 0x2, 2, 0x2);
  PATH(0x8, 0x3, 0x7, 2, 0x3);
  PATH(0x8, 0x9, 0xB, 1, 0x9);
  PATH(0x8, 0xC, 0x17, 2, 0x3);
  
  PATH(0x9, 0x1, 0x7, 1, 0x8);
  PATH(0x9, 0xA, 0xB, 1, 0xA);
  PATH(0x9, 0xC, 0x17, 1, 0x8);
  
  PATH(0xA, 0x1, 0x9, 1, 0x9);
  PATH(0xA, 0xB, 0xB, 1, 0xB);
  PATH(0xA, 0xC, 0x17, 1, 0x9);
  
  PATH(0xB, 0x1, 0x17, 1, 0xA);
  
  PATH(0xC, 0x1, 0x3, 2, 0x3);
  PATH(0xC, 0x4, 0x7, 2, 0x4);
  PATH(0xC, 0x8, 0xB, 2, 0x3);
  PATH(0xC, 0xD, 0xF, 1, 0xD);
  PATH(0xC, 0x10, 0x17, 2, 0x4);
  
  PATH(0xD, 0x1, 0xC, 1, 0xC);
  PATH(0xD, 0xE, 0xF, 1, 0xE);
  PATH(0xD, 0x10, 0x17, 1, 0xC);
  
  PATH(0xE, 0x1, 0xB, 1, 0xD);
  PATH(0xE, 0xF, 0xF, 1, 0xF);
  PATH(0xE, 0x10, 0x17, 1, 0xD);
  
  PATH(0xF, 0x1, 0x17, 1, 0xE);
  
  PATH(0x10, 0x1, 0x4, 2, 0x4);
  PATH(0x10, 0x5, 0x7, 2, 0x5);
  PATH(0x10, 0x8, 0xF, 2, 0x4);
  PATH(0x10, 0x11, 0x13, 1, 0x11);
  PATH(0x10, 0x14, 0x17, 2, 0x5);
  
  PATH(0x11, 0x1, 0xF, 1, 0x10);
  PATH(0x11, 0x12, 0x13, 1, 0x12);
  PATH(0x11, 0x14, 0x17, 1, 0x10);
  
  PATH(0x12, 0x1, 0xF, 1, 0x11);
  PATH(0x12, 0x13, 0x13, 1, 0x13);
  PATH(0x12, 0x14, 0x17, 1, 0x11);
  
  PATH(0x13, 0x1, 0x17, 1, 0x12);
  
  PATH(0x14, 0x1, 0x5, 2, 0x5);
  PATH(0x14, 0x6, 0x7, 2, 0x6);
  PATH(0x14, 0x8, 0x13, 2, 0x5);
  PATH(0x14, 0x15, 0x17, 1, 0x15);
  
  PATH(0x15, 0x1, 0x14, 1, 0x14);
  PATH(0x15, 0x16, 0x17, 1, 0x16);
  
  PATH(0x16, 0x1, 0x15, 1, 0x15);
  PATH(0x16, 0x17, 0x17, 1, 0x17);
  
  PATH(0x17, 0x1, 0x17, 1, 0x16);

#undef PATH
  
  return -1;
}

// A1 A2 A3 A4 B1 B2 B3 B4 C1 C2 C3 C4 D1 D2 D3 D4

// 12-3-4--5--67
//   8 C 10 14
//   9 D 11 15
//   A E 12 16
//   B F 13 17

uint32_t lowest_cost(struct state_t state, uint32_t max_cost) {
  uint32_t result = max_cost;
  
  if(cost(state) > max_cost) {
    return max_cost;
  }
  
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      for(int k = 0; k < 4; k++) {
        if(j == k) {
          continue;
        }
        
        int cpos = get(state, i * 4 + j);
        int epos = 8 + i * 4 + k;
        
        if(cpos == epos) {          
          state = set(state, i * 4 + j, get(state, i * 4 + k));
          state = set(state, i * 4 + k, epos);
        }
      }
    }
  }
  
  if(done(state)) {
    return cost(state);
  }
  
  uint32_t occu = occupied(state);
  
  int exits[4];
  
  for(int i = 0; i < 4; i++) {
    int possible_exit = i * 4 + 3 + 8;
    
    for(int j = 3; j >= 1; j--) {
      int pod = i * 4 + j;
      
      if(get(state, pod) == pod + 8) {
        possible_exit = pod + 7;
      } else {
        break;
      }
    }
    
    if(open(occu, possible_exit)) {
      exits[i] = possible_exit;
    } else {
      exits[i] = -1;
    }
  }
  
  for(int i = 0; i < 16; i++) {
    int pos = get(state, i);
    
    int others_done = 1;
    
    for(int j = i + 1; j < (i / 4 + 1) * 4; j++) {
      if(get(state, j) != 8 + j && !open(occu, 8 + j)) {
        others_done = 0;
      }
    }
    
    if(pos == 8 + i) {
      if(others_done) {
        continue;
      }
    }
    
    if(exits[i / 4] != -1) {
      int pc = path(pos, exits[i / 4], occu);
        
      if(pc != -1) {
        return lowest_cost(move(state, i, exits[i / 4], pc), max_cost);
      }
    }
    
    if(pos >= 8) {
      for(int p = 1; p < 8; p++) {
        int pc = path(pos, p, occu);
        
        if(pc != -1) {
          int lc = lowest_cost(move(state, i, p, pc), result);
          
          if(lc < result) {
            result = lc;
          }
        }
      }
    }
  }
  
  return result;
}

struct state_t state;

int aoc(FILE *input) {
  char start[8];
  
  fscanf(input, "#############\n");
  fscanf(input, "#...........#\n");
  fscanf(input, "###%c#%c#%c#%c###\n", &start[0], &start[2], &start[4], &start[6]);
  fscanf(input, "  #%c#%c#%c#%c#\n", &start[1], &start[3], &start[5], &start[7]);
  fscanf(input, "  #########\n");
  
  for(int i = 0; i < 8; i++) {
    int pos = 8 + i * 2 + i % 2;
    
    if(start[i] == 'A') {
      if(get(state, 0)) {
        state = set(state, 1, pos);
      } else {
        state = set(state, 0, pos);
      }
    }
    
    if(start[i] == 'B') {
      if(get(state, 4)) {
        state = set(state, 5, pos);
      } else {
        state = set(state, 4, pos);
      }
    }
    
    if(start[i] == 'C') {
      if(get(state, 8)) {
        state = set(state, 9, pos);
      } else {
        state = set(state, 8, pos);
      }
    }
    
    if(start[i] == 'D') {
      if(get(state, 12)) {
        state = set(state, 13, pos);
      } else {
        state = set(state, 12, pos);
      }
    }
  }
  
  //  9 D 11 15
  //  A E 12 16
  // #D#C#BB#AA#
  // #D#B#AA#CC#
  
  state = set(state, 2, 0x15);
  state = set(state, 3, 0x12);
  state = set(state, 6, 0x11);
  state = set(state, 7, 0xE);
  state = set(state, 10, 0xD);
  state = set(state, 11, 0x16);
  state = set(state, 14, 0x9);
  state = set(state, 15, 0xA);
  
  printf("%u\n", lowest_cost(state, INT_MAX));

  return 0;
}
