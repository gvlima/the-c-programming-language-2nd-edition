/**
 * Chapter: 6
 * Exercise: 6-01 - Our version of getword does not properly handle underscores, string constants, comments, or preprocessors
 * control lines. Write a better version.
 **/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS (sizeof keytab / sizeof(struct key))

char buf[BUFSIZE];                              /* buffer for ungetch */
int bufp = 0;                                   /* next free position in buf */

struct key {
    char *word;
    int count;
};

struct key keytab[] = {
        "auto", 0,
        "break", 0,
        "case", 0,
        "char", 0,
        "const", 0,
        "continue", 0,
        "default", 0,
        "unsigned", 0,
        "void", 0,
        "volatile", 0,
        "while", 0
};


int getword(char *, int);
int bin_search(char *, struct key *, int);

/* count keywords */
int main() {
    int n;
    char word[MAXWORD];

    while(getword(word, MAXWORD) != EOF){
        if(isalpha(word[0])){
            if((n = bin_search(word, keytab, NKEYS)) >= 0){
                keytab[n].count++;
            }
        }
    }

    for(n = 0; n < NKEYS; n++){
        if(keytab[n].count > 0){
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }

    return 0;
}

/* binserach: find word in tab[0]...tab[n-1] */
int bin_search(char *word, struct key tab[], int n){
    int cond;
    int low, high, mid;

    low = 0;
    high = n -1;

    while(low <= high){
        mid = (low+high) / 2;
        if((cond = strcmp(word, tab[mid].word)) < 0){
            high = mid - 1;
        } else if(cond > 0){
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

/* getword: get next word of character from input */
int getword(char *word, int lim){
    int c, d, getch(void), comment(void);
    void ungetch(int);
    char *w = word;

    while(isspace(c = getch()))
        ;

    if(c != EOF){
        *w++ = c;
    }

    if(isalpha(c) || c == '_' || c == '#'){
        for(; --lim > 0; w++){
            if(!isalnum(*w = getch())){
                ungetch(*w);
                break;
            }
        }
    } else if(c == '\'' || c == '"'){
        for(; --lim > 0; w++) {
            if((*w = getch()) == '\\'){
                *++w = getch();
            } else if(*w == c){
                w++;
                break;
            } else if(*w == EOF){
                break;
            }
        }
    } else if(c == '/') {
        if((d =  getch()) == '*'){
            c = comment();
        } else {
            ungetch(d);
        }
    }

    *w = '\0';
    return c;
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

/* comment: skip over comment and return a character */
int comment(void){
    int c;
    while ((c = getch()) != EOF){
        if(c == '*'){
            if((c = getch() == '/')){
                break;
            }
        } else {
            ungetch(c);
        }
    }

    return c;
}
