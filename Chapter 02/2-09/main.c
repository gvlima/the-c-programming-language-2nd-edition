/**
 * Chapter: 2
 * Exercise: 2-09 - In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x. Explain why. Use this
 * observation to write a faster version of bitcount.
 **/

#include <stdio.h>

int bitcount(unsigned int x);

int main() {
    printf("%d\n", bitcount(~0));
    return 0;
}

int bitcount(unsigned int x) {
    int b = 0;

    while (x) {
        x &= (x - 1);
        ++b;
    }

    return b;
}