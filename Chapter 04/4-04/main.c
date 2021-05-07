/**
 * Chapter: 4
 * Exercise: 4-04 - Add commands to print the top element of the stack without popping, to duplicate it, and to swap the top
 * two elements. Add a command to clear the stack.
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
void swap(void);
void duplicate(void);
void print_head(void);
void clear(void);

char buf[BUFSIZE];
double  stack[MAXVAL];
int sp = 0; /* next free stack position */
int bufp = 0;

/* reverse polish calculator */
int main() {
    int type;
    double op1, op2;
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
            case 'p':
                print_head();
                break;
            case 'd':
                if(sp > 0){
                    duplicate();
                } else {
                    printf("error: stack empty.\n");
                }
                break;
            case 's':
                if(sp > 1){
                    swap();
                } else {
                    printf("error: stack contain less then 1 item.\n");
                }
                break;
            case 'c':
                clear();
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
        printf("error: stack full, can't push %f\n", f);
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

/* swap: swap the top two elements of the stack */
void swap(){
    double temp1 = pop();
    double temp2 = pop();

    push(temp1);
    push(temp2);
}

/* duplicate: duplicate top element of the stack */
void duplicate(void){
    double temp;

    temp = pop();
    push(temp);
    push(temp);
}

/* print_head: print top element of the stack */
void print_head(){
    if(sp > 0){
        printf("%lf", stack[sp-1]);
    } else {
        printf("stack empty.\n");
    }
}

/* clear: clear stack */
void clear(){
    sp = 0;
}