/**
 * Chapter: 1
 * Exercise: 1-11 - How would you test the word count program? What kinds of inputs are most likely to uncover bugs if there are any?
 */

#include <stdio.h>

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

int main() {
    int c, nl, nw, nc, state;

    state = OUT;
    nl = 0; /* count lines */
    nw = 0; /* count words */
    nc = 0; /* count characters */

    while((c = getchar()) != EOF){
        ++nc;
        if(c == '\n'){
            ++nl;
        }
        if(c == ' ' || c == '\n' || c == '\t'){
            state = OUT;
        } else if (state == OUT){
            state = IN;
            ++nw;
        }
    }
    printf("Lines: %d, Words: %d, Characters: %d\n", nl, nw, nc);

    return 0;
}

/**
 * Comment: The input most likely to uncover bugs are those that test boundary conditions.
 * - no input
 * - no word (just new lines)
 * - one word per line
 * - no blanks or tabs
 * - words start with one or more blanks
 **/