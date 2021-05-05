/**
 * Chapter: 5
 * Exercise: 5-01 - As written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it
 * to push such a character back on the input.
 **/

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100 /* buffer for ungetch */

int getint(int *);
int getch(void);
void ungetch(int);

int bufp = 0;
char buf[BUFSIZE];

int main() {
    int num;

    getint(&num);
    printf("%i", num);

    return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn){
    int c, temp, sign;

    while(isspace(c = getch())) /* skip white space */
        ;

    if(!isdigit(c) && c != EOF && c != '+' && c != '-'){
        ungetch(c); /* it's not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if(c == '+' || c == '-'){
        temp = c;

        if(!isdigit(c = getch())){
            if(c != EOF){
                ungetch(c);
            }
            ungetch(temp);
            return temp;
        }
    }

    for(*pn = 0; isdigit(c); c = getch()){
        *pn = 10 * *pn + (c - '0');
    }

    *pn *= sign;

    if(c != EOF){
        ungetch(c);
    }

    return c;
}

/* getch: get a character */
int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c){
    if(bufp >= BUFSIZE){
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}