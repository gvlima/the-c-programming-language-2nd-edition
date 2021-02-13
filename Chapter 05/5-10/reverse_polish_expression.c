/**
 * Chapter: 5
 * Exercise: 5-10 - Write the program expr, which evaluates a reverse Polish expression from the command line, where each
 * operator or operand is a separate argument. For example expr 2 3 4 + * evaluates 2x(3+4).
 **/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100       /* max size of operand or operator */
#define NUMBER '0'      /* signal that a number was found */
#define MAXVAL 100      /* maximum depth of val stack */
#define BUFSIZE 100

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

char buf[BUFSIZE];      /* buffer for ungetch */
int bufp = 0;           /* next free position in buf */
int sp = 0;             /* next free stack position */
double val[MAXVAL];     /* value stack */

/* reverse Polish calculator */
int main(int argc, char* argv[]) {
    int type;
    double op2;
    char s[MAXOP];


    while (argc-- > 1){
        printf("argc: %i\n", argc);
        printf("argc: %s\n", argv[argc]);
    }

    while ((type = getop(s)) != EOF) {
        switch (type) {
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
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
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
void push(double f) {
    if(sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, cant push %g.\n", f);
    }
}

/* pop: pop and return top value from stack */
double pop(void) {
    if(sp>0) {
        return val[--sp];
    } else {
        printf("error: stack empty.\n");
        return 0.0;
    }
}


/* getop: get next operator or numeric operand */
int getop(char s[]) {
    int i, c;

    while((s[0] = c = getch()) == ' ' || c =='\t')
        ;

    s[1] = '\0';

    i = 0;
    if(!isdigit(c) && c!='.' && c!='-'){
        return c;
    }

    if(c=='-') {
        if(isdigit(c=getch()) || c == '.') {
            s[++i]=c;
        } else {
            if(c!=EOF) {
                ungetch(c);
            }

            return '-';
        }
    }


    if(isdigit(c)){
        while(isdigit(s[++i] =c =getch()))
            ;
    }


    if(c=='.'){
        while(isdigit(s[++i] = c=getch()))
            ;
    }

    s[i] = '\0';

    if(c!=EOF){
        ungetch(c);
    }

    return NUMBER;
}

/* getch: get a character */
int getch(void) {
    //return (bufp > 0) ? buf[--bufp] : getchar();

    if(bufp > 0){
      buf[--bufp];
    } else {

    }
}

/* ungetch: push character back on input */
void ungetch(int c) {
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}