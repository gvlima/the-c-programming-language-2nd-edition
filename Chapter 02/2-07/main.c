/**
 * Chapter: 2
 * Exercise: 2-07 - Write a function invert(x, p, n) that returns x with the n bits that begin at position p inverted (i.e.,
 * 1 changed into 0 and vice versa), leaving others unchanged.
 **/

#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main() {
    unsigned a = 2625;
    printf("%u", invert(a, 4, 3));
    return 0;
}

unsigned invert(unsigned x, int p, int n){
    return x ^ (~(~0 << n) << (p+1-n));
}