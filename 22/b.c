#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct cube {
  int valid;
  int x1, x2, y1, y2, z1, z2;
} cubes[65536];

int num_cubes;

int64_t area(struct cube *c) {
  int64_t dx = c->x2 - c->x1;
  int64_t dy = c->y2 - c->y1;
  int64_t dz = c->z2 - c->z1;
  
  return dx * dy * dz;
}

int check_overlap(struct cube *c, int x1, int x2, int y1, int y2, int z1, int z2) {
  return (x1 < c->x2 && x2 > c->x1) && (y1 < c->y2 && y2 > c->y1) && (z1 < c->z2 && z2 > c->z1);
}

int min(int a, int b) {
  return a < b ? a : b;
}

int max(int a, int b) {
  return a > b ? a : b;
}

void add_cube(int x1, int x2, int y1, int y2, int z1, int z2) {
  cubes[num_cubes].x1 = x1;
  cubes[num_cubes].x2 = x2;
  cubes[num_cubes].y1 = y1;
  cubes[num_cubes].y2 = y2;
  cubes[num_cubes].z1 = z1;
  cubes[num_cubes].z2 = z2;
  cubes[num_cubes].valid = 1;
  
  num_cubes++;
}

void remove_overlap(struct cube *c, int x1, int x2, int y1, int y2, int z1, int z2) {
  int xseg[4];
  int yseg[4];
  int zseg[4];
  
  xseg[0] = min(x1, c->x1);
  xseg[1] = max(c->x1, x1);
  xseg[2] = min(x2, c->x2);
  xseg[3] = max(c->x2, x2);
  
  yseg[0] = min(y1, c->y1);
  yseg[1] = max(c->y1, y1);
  yseg[2] = min(y2, c->y2);
  yseg[3] = max(c->y2, y2);
  
  zseg[0] = min(z1, c->z1);
  zseg[1] = max(c->z1, z1);
  zseg[2] = min(z2, c->z2);
  zseg[3] = max(c->z2, z2);
  
  for(int i = 1; i < 4; i++) {
    for(int j = 1; j < 4; j++) {
      for(int k = 1; k < 4; k++) {
        int nx1 = xseg[i - 1];
        int nx2 = xseg[i];
        int ny1 = yseg[j - 1];
        int ny2 = yseg[j];
        int nz1 = zseg[k - 1];
        int nz2 = zseg[k];
        
        if(i == 2 && j == 2 && k == 2) {
          continue;
        }
        
        if(i == 1 && x1 < c->x1) {
          continue;
        }
        
        if(i == 3 && x2 > c->x2) {
          continue;
        }
        
        if(j == 1 && y1 < c->y1) {
          continue;
        }
        
        if(j == 3 && y2 > c->y2) {
          continue;
        }
        
        if(k == 1 && z1 < c->z1) {
          continue;
        }
        
        if(k == 3 && z2 > c->z2) {
          continue;
        }
        
        if(nx2 - nx1 > 0 && ny2 - ny1 > 0 && nz2 - nz1 > 0) {
          add_cube(nx1, nx2, ny1, ny2, nz1, nz2);
        }
      }
    }
  }
  
  c->valid = 0;
}

int aoc(FILE *input) {
  char onoff[128];
  int x1, x2, y1, y2, z1, z2;
  
  while(fscanf(input, "%s x=%i..%i,y=%i..%i,z=%i..%i\n", onoff, &x1, &x2, &y1, &y2, &z1, &z2) == 7) {
    int on = !strcmp(onoff, "on");
    
    int prev_num_cubes = num_cubes;
    
    x2++;
    y2++;
    z2++;
    
    if(on) {
      add_cube(x1, x2, y1, y2, z1, z2);
    }
    
    for(int i = 0; i < prev_num_cubes; i++) {
      struct cube *c = &cubes[i];
      
      if(c->valid) {
        if(check_overlap(c, x1, x2, y1, y2, z1, z2)) {
          remove_overlap(c, x1, x2, y1, y2, z1, z2);
        }
      }
    }
  }
  
  int64_t count = 0;
  
  for(int i = 0; i < num_cubes; i++) {
    if(cubes[i].valid) {
      count += area(&cubes[i]);
    }
  }
  
  printf("%li\n", count);

  return 0;
}
