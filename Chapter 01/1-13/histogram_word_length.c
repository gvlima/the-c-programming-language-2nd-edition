/**
 * Chapter: 1
 * Exercise: 1-13 - Write a program to print a histogram of the lengths of words in its input. It is easy draw the histogram
 * with the bars horizontal; a vertical orientation is more challenging.
 */

#include <stdio.h>

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */
#define MAX_LENGTH 11 /* max length of word */
#define MAX_HISTOGRAM 15 /* max words of histogram */

int main() {
    int c, count, status, overflow, wl[MAX_LENGTH];

    status = OUT;
    count = 0;
    overflow = 0;
    for(int i=0; i < MAX_LENGTH; i++){
        wl[i]=0;
    }

    while ((c = getchar()) != EOF){
        if(c == ' ' || c == '\n' || c == '\t'){
            if(status == IN){
                if(count < MAX_LENGTH && wl[count] < MAX_HISTOGRAM){
                    ++wl[count];
                } else {
                    ++overflow;
                }
                status = OUT;
                count = 0;
            }
        } else if(status == OUT){
            status = IN;
            ++count;
        } else {
            ++count;
        }
    }

    /* horizontal bars */
    printf(" -- horizontal bar\n");
    for (int i = 0; i < MAX_LENGTH; i++) {
        printf("%i\t", i);
        for (int j = 0; j < wl[i]; j++) {
            printf("*");
        }
        printf("\n");
    }

    /* vertical bar */
    printf("\n -- vertical bar");
    for (int i = MAX_HISTOGRAM; i >= 0; i--) {
        for (int j = 0; j < MAX_LENGTH; j++) {
            if (i < wl[j]) {
                printf(" *");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < MAX_LENGTH; i++) {
        printf(" %i", i);
    }

    /* overflow */
    if(overflow > 0){
        printf("Overflow: %i", overflow);
    }

    return 0;
}