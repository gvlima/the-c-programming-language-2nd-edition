/**
 * Chapter: 4
 * Exercise: 4-08 - Suppose that there will never be more than one character of pushback. Modify getch and ungetch accordingly.
 **/

#include <stdio.h>
#define BUFSIZE 1

char buf[BUFSIZE];                       /* buffer for ungetch */
int bufp = 0;                            /* next free position in buf */

int getch(void);
void ungetch(int);

int main(void) {
    int c;

    while ((c = getch()) != '\n'){
        putchar(c);
    }

    ungetch(c);
    return 0;
}

/* getch: get a (possibly pushed-back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}