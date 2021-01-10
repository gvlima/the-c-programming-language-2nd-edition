/**
 * Chapter: 4
 * Exercise: 4-10 - An alternate organization uses getline to read an entire input line; This makes getch and ungetch
 * unnecessary. Revise the calculator to use this approach.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100 /* max size of operand or operator */
#define MAXVAL 100 /* maximum depth of val stack */
#define NUMBER '0' /* signal that a number was found */
#define MAXLINE 100

int getop(char []);
void push(double);
double pop(void);
int get_line(char s[], int limit);

double  val[MAXVAL];
char line[MAXLINE];
int li = 0;
int sp = 0;

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
        printf("error: stack full, can't push %g\n");
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

    if(line[li] == '\0'){
        if(get_line(line, MAXLINE) == 0){
            return EOF;
        } else {
            li = 0;
        }
    }

    while ((s[0] = c = line[li++]) == ' ' || c == '\t')
        ;


    s[1] = '\0';

    if(!isdigit(c) && c != '.'){
        return c; /* not a number */
    }

    i = 0;

    if(isdigit(c)){
        while (isdigit(s[++i] = c = line[li++]))
            ;

    }

    if(c == '.'){
        while (isdigit(s[++i] = c = line[li++]))
            ;
    }

    s[i] = '\0';

    li--;

    return NUMBER;
}

/* get_line: read a line into s, return length  */
int get_line(char s[], int lim){
    int c, i;

    for(i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i){
        s[i] = c;
    }

    if(c == '\n'){
        s[i]=c;
        ++i;
    }

    s[i] = '\0';
    return i;
}