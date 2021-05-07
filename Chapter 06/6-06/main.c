/**
 * Chapter: 6
 * Exercise: 6-06 - Implement a simple version of the #define processor (i.e., no arguments) suitable for use with C programs,
 * based on the routines of this section. You may also find getch and ungetch helpful.
 **/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

typedef struct nlist nlist;

struct nlist {
    nlist *next;
    char *name;
    char *defn;
};

void error(int, char *);
void skipblanks(void);
void getdef(void);

int getch(void);
int getword(char *, int);
nlist* install(char *, char *);
nlist* lookup(char *);
void undef(char *);
void ungetch(int);
void ungets( char *);

int main() {
    char w[MAXWORD];
    nlist *p;

    while (getword(w, MAXWORD) != EOF){
        if(strcmp(w, "/") == 0){
            getdef();
        } else if(!isalpha(w[0])){
            printf("%s", w);
        } else if((p = lookup(w)) == NULL){
            printf("%s", w);
        } else {
            ungets(p->defn);
        }
    }

    return 0;
}

/* getdef: get definition and install */
void getdef(void){

}

/* error: print error message and skip the rest of the line */
void error(int c, char *s){
    printf("error: %s\n", s);
    while (c != EOF && c != '\n'){
        c = getch();
    }
}

/* skipblanks: skip blank and tab characters */
void skipblanks(void){
    int c;

    while((c = getch()) == ' ' || c == '\t'){
    }

    ungetch(c);
}