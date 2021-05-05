/**
 * Chapter: 2
 * Exercise: 2-06 - Write a function setbits(x,p,n,y) that returns x with the n bits that begin at position p set to the
 * rightmost n bits of y, leaving the other bits unchanged.
 **/

#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, int y);

int main() {
    unsigned char a = 0;
    printf("%i", setbits(a, 3,3,4));
    return 0;
}

unsigned setbits(unsigned x, int p, int n, int y){
    return x & ~(~(~0 << n) << (p + 1 - n)) | (y &  ~(~0 << n)) << (p + 1 - n);
}