/**
 * Chapter: 5
 * Exercise: 5-18 - Make dcl recover from input errors.
 **/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum { NAME, PARENS, BRACKETS, ERROR };

void dcl(void);
void dirdcl(void);
int gettoken(void);

int tokentype;                                  /* type of last token */
char token[MAXTOKEN];                           /* last token string */
char name[MAXTOKEN];                            /* identifier name */
char datatype[MAXTOKEN];                        /* data type = char, int, etc */
char out[1000];                                 /* output string*/
char buf[BUFSIZE];                              /* buffer for ungetch */
int bufp = 0;                                   /* next free position in buf */

/* convert declaration to words */
int main(void) {
    while (gettoken() != EOF) {                 /* 1st token on line */
        strcpy(datatype, token);                /* is the datatype */
        out[0] = '\0';
        dcl();                                  /* parse rest of line */
        if (tokentype == ']') {
            printf("syntax error.\n");
        }
        printf("%s: %s %s\n", name, out, datatype);
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

/* dlc: parse a delcarator */
void dcl(void) {
    int ns;

    for(ns = 0; gettoken() == '*'; )              /* count *'s */
        ns++;
    dirdcl();
    while(ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
    int type;

    if(tokentype == '(') {                        /* ( dcl ) */
        dcl();
        if(tokentype != ')') {
            printf("error: missing )\n");
            printf("syntax error.\n");
            tokentype = ERROR;
            return;
        }
    } else if(tokentype == NAME) {                /* variable name */
        strcpy(name, token);
    } else {
        printf("error: expected name or (dcl)\n");
        printf("syntax error\n");
        tokentype = ERROR;
        return;
    }

    while((type=gettoken()) == PARENS || type == BRACKETS){
        if(type == PARENS) {
            strcat(out, " function returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
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
