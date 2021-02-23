/**
 * Chapter: 5
 * Exercise: 5-20 - Expand dcl to handle declarations with function argument type, qualifiers like const, and so on.
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100
#define MAXLEN 1000

enum { NAME, PARENS, BRACKETS, ERROR };

void dcl(void);
void dirdcl(void);
int gettoken(void);
void paramdcl(void);
void dclspc(char *);
int typespc(void);
int typeqaul(void);
int compare(const void*, const void*);

int tokentype;                                  /* type of last token */
char token[MAXTOKEN];                           /* last token string */
char name[MAXTOKEN];                            /* identifier name */
char datatype[MAXTOKEN];                        /* data type = char, int, etc */
char out[MAXLEN];                               /* output string*/
char buf[BUFSIZE];                              /* buffer for ungetch */
int bufp = 0;                                   /* next free position in buf */
char state;                                     /* current state of parsing */
int paramtype;                                  /* parameter type */


/* convert declaration to words */
int main(void) {
    while (gettoken() != EOF) {                 /* 1st token on line */
        strcpy(datatype, token);                /*is the datatype*/
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
        if(tokentype != ')'){
            printf("error: missing )\n");
        }
    } else if(tokentype == NAME) {               /* variable name */
        if (!name[0]) {                          /* skip if name exists */
            strcpy(name, token);
        }
    } else {
        if (paramtype){
            state = ERROR;                       /* push back tokentype without printing error msg */
        } else {
            printf("error: expected name or (dcl)\n");
        }
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
        if (type == PARENS)
            strcat(out, " function returning");
        else if (type == '(') {
            strcat(out, " function expecting");;
            paramdcl();
            strcat(out, " and returning");
        } else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

/* paramdcl: parse parameter-declaration */
void paramdcl(void) {
    char temp[MAXTOKEN];

    do {
        temp[0] = '\0';
        gettoken();
        dclspc(temp);
        paramtype = 1;
        dcl();
        paramtype = 0;

        if (tokentype == ','){
            strcat(temp, ",");
        }

        strcat(out, " ");
        strcat(out, temp);
    } while (tokentype == ',');
    if (tokentype != ')'){
        printf("missing ) in parameter declaration\n");
    }
}

/* decl-spc: parse a declarations-specifier */
void dclspc(char *type) {
    int count;

    for(count = 0; tokentype == NAME && (typespc() || typeqaul()); ++count) {
        if(count) {                             /* qualifier added? */
            strcat(type, " ");
        }

        strcat(type, token);                     /* is the datatype */
        gettoken();
    }

    state = 0;                                   /* push back previous token */
}

/* typespc: return 1 if token is a type-specifier, otherwise return 0 */
int typespc(void) {
    int compare(const void *, const void *), combination_chk();
    static const char *typetab[] = { "char", "double", "float", "int", "void" };

    if(!bsearch(&token, typetab, sizeof((typetab)) / sizeof((typetab)[0]), sizeof(char *), compare)){
        return 0; /* not a specifier */
    }

    return 1;
}

/* typequal: return 1 if token is type-qualifier, otherwise return 0 */
int typeqaul(void) {
    int compare(const void *, const void *), combination_chk();
    static const char *qualtab[] = { "const", "volatile" };

    if (!bsearch(&token, qualtab, sizeof((qualtab)) / sizeof((qualtab)[0]), sizeof(char *), compare)){
        return 0;
    }

    return 1;
}

/* compare: comparator function: return 0 if the content of s is equal to t, otherwise return a non-zero value */
int compare(const void *s, const void *t) {
    return strcmp((char *) s, *(char **) t);
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
