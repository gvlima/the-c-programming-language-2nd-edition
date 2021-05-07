/**
 * Chapter: 4
 * Exercise: 4-07 - Write a routine ungets(s) that will push back an entire string onto the input. Should ungets know
 * about buf and bufp, or should it just use ungetch?
 **/

#include <stdio.h>
#include <string.h>

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

void ungets(char *);
int getch(void);
void ungetch(int c);

int main(void) {
    int c;

    ungets("String to test \n");

    while (bufp > 0) {
        c = getch();
        putchar(c);
    }

    return 0;
}

/* ungets: put back string */
void ungets(char s[]){
    int len = strlen(s);

    while(len > 0){
        ungetch(s[--len]);
    }

}

/* getch: get a (possibly pushed-back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c) {
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/**
* ungets does not need to know about buf and bufp, the function ungetch handle those variables and error checking.
**/
