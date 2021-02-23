/**
 * Chapter: 5
 * Exercise: 5-19 - Modify undlc so that it does not add redundant parentheses to declarations.
 **/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int gettoken(void);
int nexttoken(void);

int tokentype;                                  /* type of last token */
char token[MAXTOKEN];                           /* last token string */
char out[1000];                                 /* output string*/
char buf[BUFSIZE];                              /* buffer for ungetch */
int bufp = 0;                                   /* next free position in buf */
int prevtoken;

/* undlc: convert word description to declaration */
int main(void) {
    int type;
    char temp[MAXTOKEN];

    while(gettoken() != EOF){
        strcpy(out, token);
        while((type = gettoken()) != '\n'){
            if(type == PARENS || type == BRACKETS){
                strcat(out, token);
            } else if(type == '*'){
                if((type = nexttoken()) == PARENS || type == BRACKETS){
                    sprintf(temp, "(*%s)", out);
                } else {
                    sprintf(temp, "*%s", out);
                }
                strcpy(out, temp);
            } else if(type == NAME) {
                sprintf(temp, "%s %s", token, token);
                strcpy(out, temp);
            } else {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }

    return 0;
}

/* gettoken: return next token */
int gettoken(void) {
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while((c = getch()) == ' ' || c == '\t')
        ;

    if(c == '(' ) {
        if((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if(c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']' && (*(p-1) != '\n'); )
            ;
        *p = '\0';
        if ((*(p-1)) == ']')
            return tokentype = BRACKETS;
        else
            return tokentype = ']';
    } else if(isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}

/* nexttoken: get the next token */
int nexttoken(void){
    int type;

    type = gettoken();
    prevtoken = 1;
    return type;
}

/* getch: get a character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
