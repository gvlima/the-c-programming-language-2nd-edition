/**
 * Chapter: 4
 * Exercise: 4-03 - Given the basic framework, it's straightforward to extend the calculator. Add the modulus (%)
 * operator and provisions for negative numbers.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100 /* max size of operand or operator */
#define MAXVAL 100 /* maximum depth of val stack */
#define NUMBER '0' /* signal that a number was found */
#define BUFSIZE 100 /* buffer for ungetch */

int getop(char []);
int getch(void);
void ungetch(int);
void push(double);
double pop(void);

char buf[BUFSIZE];
double  val[MAXVAL];
int sp = 0;
int bufp = 0;

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF){
        switch(type){
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if(op2 != 0){
                    push(pop() / op2);
                } else {
                    printf("error: zero divisor.\n");
                }
                break;
            case '%':
                op2 = pop();
                if(op2 != 0){
                    push(fmod(pop(), op2));
                } else {
                    printf("error: zero divisor.\n");
                }
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }
    }

    return 0;
}

/* push: push f onto value stack */
void push(double f){
    if (sp < MAXVAL){
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %f\n", f);
    }
}

/* pop: pop and return top value from stack */
double pop(void){
    if(sp > 0){
        return val[--sp];
    } else {
        printf("error: stack empty.\n");
        return 0.0;
    }
}

/* getop: get next operator of numeric operand */
int getop(char s[]){
    int i, c;

    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;


    s[1] = '\0';
    if(!isdigit(c) && c != '.'){
        return c; /* not a number */
    }

    i = 0;

    if(isdigit(c)){
        while (isdigit(s[++i] = c = getch()))
            ;

    }

    if(c == '.'){
        while (isdigit(s[++i] = c = getch()))
            ;
    }

    s[i] = '\0';

    if(c != EOF){
        ungetch(c);
    }

    return NUMBER;
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