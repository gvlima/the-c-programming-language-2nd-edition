/**
 * Chapter: 4
 * Exercise: 4-05 - Add access to library functions like sin, exp and pow. See <math.h> in Appendix B, Section 4.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100 /* max size of operand or operator */
#define MAXVAL 100 /* maximum depth of val stack */
#define NUMBER '0' /* signal that a number was found */
#define NAME 'n' /* signal that a name was found */
#define BUFSIZE 100 /* buffer for ungetch */

int getop(char []);
int getch(void);
void ungetch(int);
void push(double);
double pop(void);
void math_functions(char []);

char buf[BUFSIZE];
double  stack[MAXVAL];
int sp = 0; /* next free stack position */
int bufp = 0;

/* reverse polish calculator */
int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF){
        switch(type){
            case NUMBER:
                push(atof(s));
                break;
            case NAME:
                math_functions(s);
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
        stack[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n");
    }
}

/* pop: pop and return top value from stack */
double pop(void){
    if(sp > 0){
        return stack[--sp];
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
    i = 0;

    if(islower(c)){
        while(islower(s[++i] = c = getch()))
            ;

        s[i] = '\0';

        if(c != EOF){
            ungetch(c);
        }

        if(strlen(s) > 1){
            return NAME;
        } else {
            return c;
        }
    }

    if(!isdigit(c) && c != '.'){
        return c;
    }

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

/* math_function: supported math functions */
void math_functions(char s[]){
    double op2;

    if(strcmp(s, "sin") == 0){
        push(sin(pop()));
    } else if(strcmp(s, "cos") == 0) {
        push(cos(pop()));
    } else if(strcmp(s, "exp") == 0) {
        push(exp(pop()));
    } else if(strcmp(s, "pow") == 0) {
        op2 = pop();
        push(pow(pop(), op2));
    } else {
        printf("error: invalid function %s", s);
    }
}