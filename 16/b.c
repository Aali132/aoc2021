#include <stdio.h>
#include <string.h>
#include <limits.h>

int bits[1024 * 1024];
int num_bits;
int bit_index;

int consume_bits(int num) {
  int result = 0;
  
  for(int i = 0; i < num; i++) {
    result |= bits[bit_index++] << (num - i - 1);
  }
  
  return result;
}

int64_t parse_packet() {
  consume_bits(3);
  
  int type = consume_bits(3);
  
  int64_t result = 0;
  
  if(type == 4) {
    int more;
    
    do {
      more = consume_bits(1);
      
      result = (result << 4) | consume_bits(4);
    } while(more);
    
    return result;
  } else {
    int length_type = consume_bits(1);
    int length_packets = INT_MAX;
    int end_index = INT_MAX;
    
    if(length_type) {
      length_packets = consume_bits(11);
    } else {
      int length_bits = consume_bits(15);
      end_index = bit_index + length_bits;
    }
    
    for(int i = 0; i < length_packets; i++) {
      if(i == 0) {
        result = parse_packet();
      } else {
        if(type == 0) {
          result += parse_packet();
        } else if(type == 1) {
          result *= parse_packet();
        } else if(type == 2) {
          int64_t min = parse_packet();
          
          if(min < result) {
            result = min;
          }
        } else if(type == 3) {
          int64_t max = parse_packet();
          
          if(max > result) {
            result = max;
          }
        } else if(type == 5) {
          int gt = parse_packet();
          
          return result > gt ? 1 : 0;
        } else if(type == 6) {
          int lt = parse_packet();
          
          return result < lt ? 1 : 0;
        } else if(type == 7) {
          int eq = parse_packet();
          
          return result == eq ? 1 : 0;
        }
      }
      
      if(bit_index >= end_index) {
        break;
      }
    }
  }
  
  return result;
}

int aoc(FILE *input) {
  char line[4096];
  
  fgets(line, sizeof(line), input);
  
  strtok(line, "\r\n");
  
  int len = strlen(line);
  
  for(int i = 0; i < len; i++) {
    int hex = line[i] - '0';
    
    if(hex > 9) {
      hex -= 'A' - '0' - 10;
    }
    
    bits[num_bits++] = (hex & 8) ? 1 : 0;
    bits[num_bits++] = (hex & 4) ? 1 : 0;
    bits[num_bits++] = (hex & 2) ? 1 : 0;
    bits[num_bits++] = (hex & 1) ? 1 : 0;
  }
  
  printf("%li\n", parse_packet());

  return 0;
}
