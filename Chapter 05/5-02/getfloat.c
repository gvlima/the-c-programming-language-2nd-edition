/**
 * Chapter: 5
 * Exercise: 5-02 - Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value?
 **/

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100 /* buffer for ungetch */

int getfloat(float *);
int getch(void);
void ungetch(int);

int bufp = 0;
char buf[BUFSIZE];

int main() {
    float num;

    getfloat(&num);
    printf("%f", num);

    return 0;
}

/* getfloat: get next floating-point number from input */
int getfloat(float *pn){
    int c, sign;
    float power;

    while(isspace(c = getch())) /* skip white space */
        ;

    if(!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.'){
        ungetch(c); /* it's not a number */
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if(c == '+' || c == '-'){
        c = getch();
    }

    for(*pn = 0.0; isdigit(c); c = getch()){
        *pn = 10.0 * *pn + (c - '0'); /* integer part */
    }

    if(c == '.'){
        c = getch();
    }

    for(power = 1.0; isdigit(c); c = getch()){
        *pn = 10.0 * *pn + (c - '0'); /* fractional part */
        power *= 10.0;
    }

    *pn *= sign / power;

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