/**
 * Chapter: 6
 * Exercise: 6-04 - Write a program that prints the distinct words in its input sorted into decreasing order of frequency of
 * occurrence. Precede each word by its count.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 1000

char buf[BUFSIZE];                              /* buffer for ungetch */
int bufp = 0;                                   /* next free position in buf */

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

int getword(char *, int);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char* strdpl(char *);

int main() {
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;

    while(getword(word,MAXWORD) != EOF){
        if(isalpha(word[0])){
            root = addtree(root, word);
        }
    }

    treeprint(root);

    return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w){
    int cond;

    if(p == NULL) {
        p = talloc();
        p->word = strdpl(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if((cond = strcmp(w, p->word)) == 0){
        p->count++;
    } else {
        if(p->count < p->left->count){

        }
        p->left = addtree(p->left, w);
    }

    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p){
    if(p != NULL){
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

/* talloc: make a tnode */
struct tnode *talloc(void){
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strdlp: make a duplicate of s */
char* strdpl(char *s){
    char *p;

    p = (char *) malloc(strlen(s)+1);
    if(p != NULL){
        strcpy(p, s);
    }

    return p;
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