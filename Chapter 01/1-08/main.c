/**
 * Chapter: 1
 * Exercise: 1-8 - Write a program to count blanks, tabs, and newlines.
 */

#include <stdio.h>

int main() {
    int c, tc, bsc, nlc;

    tc = 0; /* tab count */
    bsc = 0; /* blank space count */
    nlc = 0; /* new line count */

    while ((c = getchar()) != EOF){
        if(c == '\t'){
            ++tc;
        } else if (c == ' '){
            ++bsc;
        } else if (c == '\n'){
            ++nlc;
        }
    }
    printf("tab count: %i - blank spaces count: %i, new lines count: %i", tc, bsc, nlc);

    return 0;
}