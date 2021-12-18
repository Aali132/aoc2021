#include <stdio.h>
#include <stdlib.h>

struct node {
  int value;
  
  struct node *left;
  struct node *right;
};

int is_pair(struct node *n) {
  return n->left || n->right;
}

struct node *new(int value, struct node *left, struct node *right) {
  struct node *result = malloc(sizeof(*result));
  
  result->value = value;
  result->left = left;
  result->right = right;
  
  return result;
}

void destroy(struct node *n) {
  if(is_pair(n)) {
    destroy(n->left);
    destroy(n->right);
  } else {
    free(n);
  }
}

struct node *first_right(struct node *n) {
  if(is_pair(n)) {
    return first_right(n->left);
  } else {
    return n;
  }
}

struct node *first_left(struct node *n) {
  if(is_pair(n)) {
    return first_left(n->right);
  } else {
    return n;
  }
}

int explode(struct node *n, int level, struct node *near_left, struct node *near_right) {
  if(is_pair(n)) {
    if(level == 4) {
      n->value = 0;
      
      if(near_left) {
        near_left->value += n->left->value;
      }
      
      free(n->left);
      n->left = 0;
      
      if(near_right) {
        near_right->value += n->right->value;
      }
      
      free(n->right);
      n->right = 0;
      
      return 1;
    } else {
      if(is_pair(n->right)) {
        if(explode(n->left, level + 1, near_left, first_right(n->right))) {
          return 1;
        }
      } else {
        if(explode(n->left, level + 1, near_left, n->right)) {
          return 1;
        }
      }
      
      if(is_pair(n->left)) {
        if(explode(n->right, level + 1, first_left(n->left), near_right)) {
          return 1;
        }
      } else {
        if(explode(n->right, level + 1, n->left, near_right)) {
          return 1;
        }
      }
    }
  }
  
  return 0;
}

int split(struct node *n) {
  if(is_pair(n)) {
    if(split(n->left)) {
      return 1;
    }
    
    if(split(n->right)) {
      return 1;
    }
  } else if(n->value > 9) {
    n->left = new(n->value / 2, 0, 0);
    n->right = new((n->value + 1) / 2, 0, 0);
    
    return 1;
  }
  
  return 0;
}

struct node *add(struct node *a, struct node *b) {
  if(!a) {
    return b;
  }
  
  struct node *sum = new(0, a, b);
  
  while(1) {
    if(explode(sum, 0, 0, 0)) {
      continue;
    } else if(split(sum)) {
      continue;
    } else {
      break;
    }
  }
  
  return sum;
}

struct node *parse(char **line) {
  if(**line == '[') {
    (*line)++;
    struct node *left = parse(line);
    (*line)++;
    struct node *right = parse(line);
    (*line)++;
    
    return new(0, left, right);
  } else if(**line >= '0' && **line <= '9') {
    int value = **line - '0';
    
    (*line)++;
    
    return new(value, 0, 0);
  }
  
  exit(-1);
}

int64_t mag(struct node *n) {
  if(is_pair(n)) {
    return mag(n->left) * 3 + mag(n->right) * 2;
  } else {
    return n->value;
  }
}

char line[1024][1024];
int num_values;

int64_t max_mag;

int64_t maglines(int line1, int line2) {
  char *parser;
  
  parser = line[line1];
  
  struct node *a = parse(&parser);
  
  parser = line[line2];
  
  struct node *b = parse(&parser);
  
  struct node *sum = add(a, b);
  
  int64_t result = mag(sum);
  
  destroy(sum);
  
  return result;
}

int aoc(FILE *input) {
  while(fgets(line[num_values++], sizeof(*line), input));
  
  num_values -= 1;
  
  for(int i = 0; i < num_values; i++) {
    for(int j = i + 1; j < num_values; j++) {
      int64_t magleft = maglines(i, j);
      int64_t magright = maglines(j, i);
      
      if(magleft > max_mag) {
        max_mag = magleft;
      }
      
      if(magright > max_mag) {
        max_mag = magright;
      }
    }
  }
  
  printf("%li\n", max_mag);

  return 0;
}
