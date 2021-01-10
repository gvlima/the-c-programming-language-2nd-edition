/**
 * Chapter: 4
 * Exercise: 4-09 - Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what their properties ought to
 * be if an EOF is pushed back, then implement your design.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100 /* max size of operand or operator */
#define MAXVAL 100 /* maximum depth of val stack */
#define NUMBER '0' /* signal that a number was found */
#define BUFSIZE 100 /* buffer for ungetch */

int getop(char []);
int getch(void);
void ungetch(int);
void push(double);
double pop(void);

int buf[BUFSIZE]; /* buffer for ungetch */
double stack[MAXVAL];
int sp = 0; /* next free stack position */
int bufp = 0;

/* reverse polish calculator */
int main() {
    int type, i, var;
    double op2, v, variable[26];
    char s[MAXOP];

    var = 0;

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
            case '=':
                pop();
                if(var >= 'A' && var <= 'Z') {
                    variable[var - 'A'] = pop();
                } else {
                    printf("error: no variable name.\n");
                }
                break;
            case '\n':
                v = pop();
                printf("\t%.8g\n", pop());
                break;
            default:
                if(type >= 'A' && type <= 'Z'){
                    push(variable[type - 'A']);
                } else if (type == 'v') {
                    push(v);
                } else {
                    printf("error: unknown command %s\n", s);
                }
                break;
        }
        var = type;
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
    if(!isdigit(c) && c != '.'){
        return c;
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