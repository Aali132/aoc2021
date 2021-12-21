#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_DISTANCE 65536

struct {
  int b1;
  int b2;
  int valid;
} dist[MAX_DISTANCE];

int beacons[32 * 64][3];

int num_beacons;

void add_beacon(int x, int y, int z) {
  for(int b = 0; b < num_beacons; b++) {
    if(x == beacons[b][0] && y == beacons[b][1] && z == beacons[b][2]) {
      return;
    }
  }
  
  beacons[num_beacons][0] = x;
  beacons[num_beacons][1] = y;
  beacons[num_beacons][2] = z;
  
  num_beacons++;
}

struct {
  int beacons[32][3];
  int num_beacons;
  int transform[3][4];
  int done;
} scanners[64];

int num_scanners;
int scanners_done;

int beacon_coord(int s, int b, int c) {
  int x = scanners[s].beacons[b][0];
  int y = scanners[s].beacons[b][1];
  int z = scanners[s].beacons[b][2];
  
  return x * scanners[s].transform[c][0] + y * scanners[s].transform[c][1] + z * scanners[s].transform[c][2] + scanners[s].transform[c][3];
}

int distance(int s, int b1, int b2, int c) {
  return abs(scanners[s].beacons[b1][c] - scanners[s].beacons[b2][c]);
}

int sign(int a, int b) {
  return (a == b) ? 1 : ((a == -b) ? -1 : 0);
}

int offset(int b1, int b2, int s, int sb1, int sb2, int c) {
  return ((beacons[b1][c] + beacons[b2][c]) - (beacon_coord(s, sb1, c) + beacon_coord(s, sb2, c))) / 2;
}

int find_transform(int b1, int b2, int s, int sb1, int sb2) {
  int xd1 = beacons[b1][0] - beacons[b2][0];
  int yd1 = beacons[b1][1] - beacons[b2][1];
  int zd1 = beacons[b1][2] - beacons[b2][2];
  
  int xd2 = scanners[s].beacons[sb1][0] - scanners[s].beacons[sb2][0];
  int yd2 = scanners[s].beacons[sb1][1] - scanners[s].beacons[sb2][1];
  int zd2 = scanners[s].beacons[sb1][2] - scanners[s].beacons[sb2][2];
  
  scanners[s].transform[0][0] = sign(xd1, xd2);
  scanners[s].transform[0][1] = sign(xd1, yd2);
  scanners[s].transform[0][2] = sign(xd1, zd2);
  scanners[s].transform[1][0] = sign(yd1, xd2);
  scanners[s].transform[1][1] = sign(yd1, yd2);
  scanners[s].transform[1][2] = sign(yd1, zd2);
  scanners[s].transform[2][0] = sign(zd1, xd2);
  scanners[s].transform[2][1] = sign(zd1, yd2);
  scanners[s].transform[2][2] = sign(zd1, zd2);
  
  int sumx = abs(scanners[s].transform[0][0]) + abs(scanners[s].transform[0][1]) + abs(scanners[s].transform[0][2]);
  int sumy = abs(scanners[s].transform[0][0]) + abs(scanners[s].transform[0][1]) + abs(scanners[s].transform[0][2]);
  int sumz = abs(scanners[s].transform[0][0]) + abs(scanners[s].transform[0][1]) + abs(scanners[s].transform[0][2]);
  
  if(sumx != 1 || sumy != 1 || sumz != 1) {
    return 0;
  }
  
  scanners[s].transform[0][3] = 0;
  scanners[s].transform[1][3] = 0;
  scanners[s].transform[2][3] = 0;
  
  scanners[s].transform[0][3] = offset(b1, b2, s, sb1, sb2, 0);
  scanners[s].transform[1][3] = offset(b1, b2, s, sb1, sb2, 1);
  scanners[s].transform[2][3] = offset(b1, b2, s, sb1, sb2, 2);
  
  return 1;
}

int check_overlap(int s) {
  int overlap = 0;
  
  for(int i = 0; i < num_beacons; i++) {
    for(int j = 0; j < scanners[s].num_beacons; j++) {
      int x = beacons[i][0] - beacon_coord(s, j, 0);
      int y = beacons[i][1] - beacon_coord(s, j, 1);
      int z = beacons[i][2] - beacon_coord(s, j, 2);
      
      if(x == 0 && y == 0 && z == 0) {
        overlap++;
        
        if(overlap == 12) {
          return overlap;
        }
      }
    }
  }
  
  return overlap;
}

void add_all_beacons(int s) {
  for(int b = 0; b < scanners[s].num_beacons; b++) {
    add_beacon(beacon_coord(s, b, 0), beacon_coord(s, b, 1), beacon_coord(s, b, 2));
  }
  
  scanners[s].done = 1;
  scanners_done++;
}

void check_scanner(int s) {
  memset(dist, 0, sizeof(dist));
  
  for(int b1 = 0; b1 < scanners[s].num_beacons; b1++) {
    for(int b2 = b1 + 1; b2 < scanners[s].num_beacons; b2++) {
      int xd = abs(scanners[s].beacons[b1][0] - scanners[s].beacons[b2][0]);
      int yd = abs(scanners[s].beacons[b1][1] - scanners[s].beacons[b2][1]);
      int zd = abs(scanners[s].beacons[b1][2] - scanners[s].beacons[b2][2]);
      
      int d = xd + yd + zd;
      
      dist[d].b1 = b1;
      dist[d].b2 = b2;
      dist[d].valid = 1;
    }
  }
  
  for(int b1 = 0; b1 < num_beacons; b1++) {
    for(int b2 = b1 + 1; b2 < num_beacons; b2++) {
      int xd = abs(beacons[b1][0] - beacons[b2][0]);
      int yd = abs(beacons[b1][1] - beacons[b2][1]);
      int zd = abs(beacons[b1][2] - beacons[b2][2]);
      
      int d = xd + yd + zd;
      
      if(dist[d].valid) {
        if(find_transform(b1, b2, s, dist[d].b1, dist[d].b2)) {
          int overlap = check_overlap(s);
          
          if(overlap >= 12) {
            add_all_beacons(s);
            
            return;
          }
        }
      }
    }
  }
}

int aoc(FILE *input) {
  char line[1024];
  int x, y, z;
  
  while(fgets(line, sizeof(line), input)) {
    int result = sscanf(line, "%i,%i,%i", &x, &y, &z);
    
    if(result == 3) {
      int b = scanners[num_scanners].num_beacons;
      
      scanners[num_scanners].beacons[b][0] = x;
      scanners[num_scanners].beacons[b][1] = y;
      scanners[num_scanners].beacons[b][2] = z;
      
      scanners[num_scanners].num_beacons++;
    } else {
      if(scanners[num_scanners].num_beacons) {
        scanners[num_scanners].transform[0][0] = 1;
        scanners[num_scanners].transform[1][1] = 1;
        scanners[num_scanners].transform[2][2] = 1;
        
        num_scanners++;
      }
    }
  }
  
  if(scanners[num_scanners].num_beacons) {
    num_scanners++;
  }
  
  add_all_beacons(0);
  
  while(scanners_done < num_scanners) {
    for(int s = 1; s < num_scanners; s++) {
      if(!scanners[s].done) {
        check_scanner(s);
      }
    }
  }
  
  int max_dist = 0;
  
  for(int s1 = 0; s1 < num_scanners; s1++) {
    for(int s2 = s1 + 1; s2 < num_scanners; s2++) {
      int distx = abs(scanners[s1].transform[0][3] - scanners[s2].transform[0][3]);
      int disty = abs(scanners[s1].transform[1][3] - scanners[s2].transform[1][3]);
      int distz = abs(scanners[s1].transform[2][3] - scanners[s2].transform[2][3]);
      
      int manhattan = distx + disty + distz;
      
      if(manhattan > max_dist) {
        max_dist = manhattan;
      }
    }
  }
  
  printf("%i\n", max_dist);

  return 0;
}
