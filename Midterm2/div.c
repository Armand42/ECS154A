#include <stdio.h>
#include <stdlib.h>

void my_div(unsigned int dividend, unsigned int divisor, 
         unsigned int* quotient, unsigned int *remainder);
         
void my_div(unsigned int dividend, unsigned int divisor, 
         unsigned int* quotient, unsigned int *remainder){
  
  *quotient = 0;
  *remainder = 0;
  
  // dividend = 25
  // divisor = 3

  // expect: return quotient = 8, remainder = 1

  // mask = 10000000000000000000000000000000 (32 bits)

  unsigned int mask = 1 << 31; //start at the most signifcant bit of the dividend
  //  mask = mask / 2
  // iter 0: mask = 10000000000000000000000000000000  (bit 32th is on)
  // iter 1: mask = 01000000000000000000000000000000   (bit 31th is on)
  // iter 2: mask = 00100000000000000000000000000000
  // ..
  // iter 31: mask = 00000000000000000000000000000001  
  // iter 32: mask = 00000000000000000000000000000000

  for(; mask > 0; mask >>= 1){
  
    //make space for the new bit we need to bring in 
    //automatically default that value to 0
    *remainder <<= 1;  // remainder = 1
    *quotient <<= 1;   // quotient = 1
    
    if(dividend & mask){
      *remainder |= 1;
    }
    
    if(divisor <= *remainder){
      *remainder -= divisor;
      *quotient |= 1;
    }
  
  }
  
  
}//div

int main(int argc, char** argv){
  unsigned int dividend, divisor, quotient, remainder;
  
  sscanf(argv[1], "%u", &dividend);
  sscanf(argv[2], "%u", &divisor);
  my_div(dividend, divisor, &quotient, &remainder);
  printf("%u / %u = %u R %u\n", dividend, divisor, quotient, remainder);

  //printf("%u / %u = %u R %u\n", dividend, divisor, quotient, remainder);
  return 0;
}
