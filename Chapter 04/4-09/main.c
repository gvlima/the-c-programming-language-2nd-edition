/**
 * Chapter: 4
 * Exercise: 4-09 - Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what their properties ought to
 * be if an EOF is pushed back, then implement your design.
 **/

#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;	/* next free position in buf */

int getch(void);
void ungetch(int);

int main(void) {
    int c;

    while ((c = getch()) != EOF){
        putchar(c);
    }

    return 0;
}

/* getch: get a (possibly pushed-back) character */
int getch(void) {
    return bufp > 0 ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else if (c != EOF) {
        buf[bufp++] = c;
    } else if (c == EOF) {
        printf("ERROR: EOF Can't be stored as a char\n");
        exit(EXIT_FAILURE);
    }
}