/**
 * Chapter: 7
 * Exercise: 7-02 - Write a program that will print arbitrary input in a sensible way. As a minimum, ith should print
 * non-graphic characters in octal or hexadecimal according to local custom, and break long text lines.
 **/

#include <stdio.h>
#include <ctype.h>

#define MAX_LINE 100
#define OCT_LEN 6

int increment(int, int);

int main() {
    int c, pos;
    pos = 0;

    while((c=getchar()) != EOF){
        if(isgraph(c)){
            pos = increment(pos, 1);
            putchar(c);
        } else {
            pos = increment(pos, OCT_LEN);
            printf("\\%03o ", c);

            if(c == '\n'){
                pos = 0;
                putchar('\n');
            }
        }
    }

    return 0;
}

/* increment: increment position */
int increment(int pos, int n){
    if(pos + n < MAX_LINE){
        return pos+n;
    } else {
        putchar("\n");
        return n;
    }
}