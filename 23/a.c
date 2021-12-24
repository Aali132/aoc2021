#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>

uint32_t cost(uint64_t state) {
  return state >> 32;
}

uint64_t add(uint64_t state, uint32_t c) {
  return (state & 0xFFFFFFFF) | (((uint64_t)(cost(state) + c)) << 32);
}

int get(uint64_t state, int pod) {
  return (state >> (pod * 4)) & 0xF;
}

uint64_t set(uint64_t state, int pod, int pos) {
  uint64_t mask = ((uint64_t)0xF) << (pod * 4);
  
  return (state & (~mask)) | (((uint64_t)pos) << (pod * 4));
}

uint16_t occupied(uint64_t state) {
  uint16_t result = 0;
  
  for(int i = 0; i < 8; i++) {
    result |= 1 << get(state, i);
  }
  
  return result;
}

int open(uint16_t occu, int pos) {
  return !(occu & (1 << pos));
}

int done(uint64_t state) {
  return (state & 0xFFFFFFFF) == 0xFEDCBA98;
}

uint64_t move(uint64_t state, int pod, int pos, int c) {
  if(pod >= 2) {
    c *= 10;
  }
  
  if(pod >= 4) {
    c *= 10;
  }
  
  if(pod >= 6) {
    c *= 10;
  }
  
  return add(set(state, pod, pos), c);
}

int path(int from, int to, uint16_t occu) {
  if(from == to) {
    return 0;
  }
  
#define PATH(F, MIN, MAX, C, T) if(from == (F) && to >= (MIN) && to <= (MAX) && open(occu, (T))) { int pc = path((T), to, occu); if(pc != -1) { return (C) + pc; } else { return -1; } }

  PATH(0x1, 0x1, 0xF, 1, 0x2);
  
  PATH(0x2, 0x1, 0x1, 1, 0x1);
  PATH(0x2, 0x3, 0x7, 2, 0x3);
  PATH(0x2, 0x8, 0x9, 2, 0x8);
  PATH(0x2, 0xA, 0xF, 2, 0x3);
  
  PATH(0x3, 0x1, 0x2, 2, 0x2);
  PATH(0x3, 0x4, 0x7, 2, 0x4);
  PATH(0x3, 0x8, 0x9, 2, 0x8);
  PATH(0x3, 0xA, 0xB, 2, 0xA);
  PATH(0x3, 0xC, 0xF, 2, 0x4);

  PATH(0x4, 0x1, 0x3, 2, 0x3);
  PATH(0x4, 0x5, 0x7, 2, 0x5);
  PATH(0x4, 0x8, 0x9, 2, 0x3);
  PATH(0x4, 0xA, 0xB, 2, 0xA);
  PATH(0x4, 0xC, 0xD, 2, 0xC);
  PATH(0x4, 0xE, 0xF, 2, 0x5);
  
  PATH(0x5, 0x1, 0x4, 2, 0x4);
  PATH(0x5, 0x6, 0x7, 2, 0x6);
  PATH(0x5, 0x8, 0xB, 2, 0x4);
  PATH(0x5, 0xC, 0xD, 2, 0xC);
  PATH(0x5, 0xE, 0xF, 2, 0xE);
  
  PATH(0x6, 0x1, 0x5, 2, 0x5);
  PATH(0x6, 0x7, 0x7, 2, 0x7);
  PATH(0x6, 0x7, 0x7, 1, 0x7);
  PATH(0x6, 0x8, 0xD, 2, 0x5);
  PATH(0x6, 0xE, 0xF, 2, 0xE);
  
  PATH(0x7, 0x1, 0xF, 1, 0x6);
  
  PATH(0x8, 0x1, 0x2, 2, 0x2);
  PATH(0x8, 0x3, 0x7, 2, 0x3);
  PATH(0x8, 0x9, 0x9, 1, 0x9);
  
  PATH(0x9, 0x1, 0x7, 1, 0x8);
  
  PATH(0xA, 0x1, 0x3, 2, 0x3);
  PATH(0xA, 0x4, 0x7, 2, 0x4);
  PATH(0xA, 0xB, 0xB, 1, 0xB);
  
  PATH(0xB, 0x1, 0x7, 1, 0xA);
  
  PATH(0xC, 0x1, 0x4, 2, 0x4);
  PATH(0xC, 0x5, 0x7, 2, 0x5);
  PATH(0xC, 0xD, 0xD, 1, 0xD);
  
  PATH(0xD, 0x1, 0x7, 1, 0xC);
  
  PATH(0xE, 0x1, 0x5, 2, 0x5);
  PATH(0xE, 0x6, 0x7, 2, 0x6);
  PATH(0xE, 0xF, 0xF, 1, 0xF);
  
  PATH(0xF, 0x1, 0x7, 1, 0xE);
  
#undef PATH
  
  return -1;
}

void print_state(uint64_t state) {
  char pos[16];
  
  memset(pos, '.', sizeof(pos));
  
  for(int i = 0; i < 8; i++) {
    pos[get(state, i)] = 'A' + i / 2;
  }
  
  printf("#############\n");
  printf("#%c%c.%c.%c.%c.%c%c#\n", pos[1], pos[2], pos[3], pos[4], pos[5], pos[6], pos[7]);
  printf("###%c#%c#%c#%c###\n", pos[8], pos[10], pos[12], pos[14]);
  printf("  #%c#%c#%c#%c#\n", pos[9], pos[11], pos[13], pos[15]);
  printf("  #########\n");
}

// A1 A2 B1 B2 C1 C2 D1 D2

// 12-3-4-5-67
//   8 A C E
//   9 B D F

uint32_t lowest_cost(uint64_t state, uint32_t max_cost) {
  uint32_t result = max_cost;
  
  if(cost(state) > max_cost) {
    return max_cost;
  }
  
  //printf("cost %i max %i\n", cost(state), max_cost);
  //print_state(state);
  
  for(int i = 0; i < 4; i++) {
    int one = i * 2;
    int two = one + 1;
    int pos = 9 + one;
    
    if(get(state, one) == pos) {
      state = set(state, one, get(state, two));
      state = set(state, two, pos);
    }
  }
  
  if(done(state)) {
    //printf("done %i\n\n", cost(state));
    
    return cost(state);
  }
  
  uint16_t occu = occupied(state);
  
  for(int i = 0; i < 8; i++) {
    int pos = get(state, i);
    
    if(pos == 8 + i) {
      if((i % 2) || get(state, i + 1) == 8 + i + 1) {
        continue;
      }
    }
    
    if(((pos & 0x9) == 0x9) && !open(occu, pos - 1)) {
      continue;
    }
    
    if(pos < 8) {
      int end2 = 9 + (i / 2) * 2;
      int end1 = 8 + (i / 2) * 2;
      
      int path2 = path(pos, end2, occu);
      
      if(path2 != -1) {
        return lowest_cost(move(state, i, end2, path2), max_cost);
      }
      
      if((i % 2) == 0) {
        if(get(state, i + 1) == end2) {
          int path1 = path(pos, end1, occu);
          
          if(path1 != -1) {
            return lowest_cost(move(state, i, end1, path1), max_cost);
          }
        }
      }
    } else {
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

int aoc(FILE *input) {
  char start[8];
  
  fscanf(input, "#############\n");
  fscanf(input, "#...........#\n");
  fscanf(input, "###%c#%c#%c#%c###\n", &start[0], &start[2], &start[4], &start[6]);
  fscanf(input, "  #%c#%c#%c#%c#\n", &start[1], &start[3], &start[5], &start[7]);
  fscanf(input, "  #########\n");
  
  uint64_t state = 0;
  
  for(int i = 0; i < 8; i++) {
    if(start[i] == 'A') {
      if(get(state, 0)) {
        state = set(state, 1, 8 + i);
      } else {
        state = set(state, 0, 8 + i);
      }
    }
    
    if(start[i] == 'B') {
      if(get(state, 2)) {
        state = set(state, 3, 8 + i);
      } else {
        state = set(state, 2, 8 + i);
      }
    }
    
    if(start[i] == 'C') {
      if(get(state, 4)) {
        state = set(state, 5, 8 + i);
      } else {
        state = set(state, 4, 8 + i);
      }
    }
    
    if(start[i] == 'D') {
      if(get(state, 6)) {
        state = set(state, 7, 8 + i);
      } else {
        state = set(state, 6, 8 + i);
      }
    }
  }
  
  printf("%u\n", lowest_cost(state, INT_MAX));

  return 0;
}
