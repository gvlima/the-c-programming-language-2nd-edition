/**
 * Chapter: 2
 * Exercise: 2-08 - Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n bit positions.
 **/

#include <stdio.h>

unsigned rightrot(unsigned x, int n);
int wordlength(void);

int main(void) {
    unsigned x = 0x5;
    int n = 8;

    printf("word length: %i\n", wordlength());
    printf("x (after rotate): %u\n", rightrot(x, n));

    return 0;
}

/* rightrot: rotate x to the right by n positions */
unsigned rightrot(unsigned x, int n){
    int rbit;

    while(n-- > 0){
        rbit = (x & 1) << (wordlength() -1);
        x = x >> 1;
        x = x | rbit;
    }

    return x;
}

/* wordlength: return the size of an integer */
int wordlength(void){
    int x = ~0, i=0;

    while (x != 0) {
        x <<= 1;
        ++i;
    }

    return i;
}
