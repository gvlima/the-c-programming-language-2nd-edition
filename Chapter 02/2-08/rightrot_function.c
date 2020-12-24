/**
 * Chapter: 2
 * Exercise: 2-08 - Write a function rightrot(x,n) that returns the value of the integer x rotated to the right by n bit positions.
 **/


#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main(void) {
    int a = 1;
    return 0;
}

unsigned rightrot(unsigned x, int n){
    int wordlength(void);
    int rbit;

    while (n-- > 0){
        rbit = (x & 1) << (wordlength() -1);
        x = x >> 1;
        x = x
    }
}