#include <stdio.h>
#include <string.h>

int bits[1024 * 1024];
int num_bits;
int bit_index;

int version_sum;

int consume_bits(int num) {
  int result = 0;
  
  for(int i = 0; i < num; i++) {
    result |= bits[bit_index++] << (num - i - 1);
  }
  
  return result;
}

void parse_packet() {
  int version = consume_bits(3);
  int type = consume_bits(3);
  
  version_sum += version;
  
  if(type == 4) {
    int literal = 0;
    int more;
    
    do {
      more = consume_bits(1);
      
      literal = (literal << 4) | consume_bits(4);
    } while(more);
  } else {
    int length_type = consume_bits(1);
    
    if(length_type) {
      int length_packets = consume_bits(11);
      
      for(int i = 0; i < length_packets; i++) {
        parse_packet();
      }
    } else {
      int length_bits = consume_bits(15);
      int end_index = bit_index + length_bits;
      
      while(bit_index < end_index) {
        parse_packet();
      }
    }
  }
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
  
  parse_packet();
  
  printf("%i\n", version_sum);

  return 0;
}
