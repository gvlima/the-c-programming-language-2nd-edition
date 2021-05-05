/**
 * Chapter: 1
 * Exercise: 1-9 - Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank.
 */

#include <stdio.h>

int main() {
    int c, before;
    before = NULL;

    while ((c = getchar()) != EOF){
        if(c != ' ' || before != ' '){
            putchar(c);
        }

        before = c;
    }

    return 0;
}