/**
 * Chapter: 4
 * Exercise: 4-14 - Define a macro swap(t,x,y) that interchanges two arguments of type t. (Block structure will help.)
 **/

#include <stdio.h>

#define SWAP(t,x,y) {t tmp;\
                       tmp = y;\
                       y = x;\
                       x = tmp;\
                    }

int main(void) {
    int a = 100;
    int b = 50;

    SWAP(int, a, b);
    printf("A = %d B = %d\n", a, b);

    return 0;
}