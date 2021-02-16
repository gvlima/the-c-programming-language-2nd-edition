/**
 * Chapter: 1
 * Exercise: 1-20 - Write a program detab that replaces tabs in the input with the proper number of blanks to space to the
 * next tab stop. Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter?
 **/

#include <stdio.h>
#define TABINC 8

int main() {
    int c, blank, pos;
    pos = 1;

    while((c=getchar()) != EOF){
        if(c == '\t') {
            blank = TABINC - ((pos - 1) % TABINC);
            while(blank > 0) {
                putchar('#');
                ++pos;
                --blank;
            }
        } else if( c == '\n') {
            putchar(c);
            pos = 1;
        } else {
            putchar(c);
            ++pos;
        }
    }

    return 0;
}