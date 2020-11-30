/**
 * Chapter: 1
 * Exercise: 1-14 - Write a program to print a histogram of the frequencies of different characters in its input.
 */

#include <stdio.h>

#define MAX 128

int main() {
    int c, i;
    int cc[MAX]; /* character count */

    for(i=0; i<MAX; i++){
        cc[i]=0;
    }

    while ((c = getchar()) != EOF){
        if(c < MAX){
            ++cc[c];
        }
    }

    /* horizontal bars */
    printf(" -- horizontal bar\n");
    for (i = 32; i < MAX; i++) {
        printf("%c\t", i);
        for (int j = 0; j < cc[i]; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}

/**
 * Comment: The first 32 codes of ASCII character set are non-printing characters and rarely used for their original purpose.
 **/