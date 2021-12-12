#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NODES 256
#define PATHS (1024 * 1024)

struct node {
  char name[256];
  int edges[NODES];
  int num_edges;
  int small;
} nodes[NODES];

int num_nodes;

int start_node;
int end_node;

int get_node(char *name) {
  for(int n = 0; n < num_nodes; n++) {
    if(!strcmp(nodes[n].name, name)) {
      return n;
    }
  }
  
  strcpy(nodes[num_nodes].name, name);
  
  nodes[num_nodes].small = islower(*name);
  
  if(!strcmp(name, "start")) {
    start_node = num_nodes;
  }
  
  if(!strcmp(name, "end")) {
    end_node = num_nodes;
  }
  
  return num_nodes++;
}

void connect_nodes(int n1, int n2) {
  struct node *node1 = &nodes[n1];
  struct node *node2 = &nodes[n2];
  
  node1->edges[node1->num_edges++] = n2;
  node2->edges[node2->num_edges++] = n1;
}

struct path {
  int visited[NODES];
  int valid;
  int small;
} paths[PATHS];

int num_paths;

void traverse_node(int p, int node) {
  if(nodes[node].small && paths[p].visited[node]) {
    if(paths[p].small || node == start_node) {
      return;
    }
    
    paths[p].small = 1;
  }
  
  paths[p].visited[node] = 1;
  
  if(node == end_node) {
    paths[p].valid = 1;
    
    return;
  }
  
  for(int e = 1; e < nodes[node].num_edges; e++) {
    int new_path = num_paths++;
    
    memcpy(&paths[new_path], &paths[p], sizeof(paths[p]));
    
    traverse_node(new_path, nodes[node].edges[e]);
  }
  
  traverse_node(p, nodes[node].edges[0]);
}

int aoc(FILE *input) {
  char line[4096];
  
  while(fgets(line, sizeof(line), input)) {
    strtok(line, "\r\n");
    
    char *node1 = strtok(line, "-");
    char *node2 = strtok(0, "-");
    
    int n1 = get_node(node1);
    int n2 = get_node(node2);
    
    connect_nodes(n1, n2);
  }
  
  num_paths = 1;
  
  traverse_node(0, start_node);
  
  int valid_paths = 0;
  
  for(int p = 0; p < PATHS; p++) {
    if(paths[p].valid) {
      valid_paths++;
    }
  }
  
  printf("%i\n", valid_paths);

  return 0;
}
