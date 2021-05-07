/**
 * Chapter: 6
 * Exercise: 6-03 - Write a cross-referencer that prints a list of all words in a document, and, for each word, a list of
 * the line numbers on which it occurs. Remove noise words like "the", "and" and so on.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 10000
#define LINE_NUMBERS 10
#define MIN_LENGHT 3
#define TRUE 1
#define FALSE 0

char buf[BUFSIZE];                              /* buffer for ungetch */
int bufp = 0;                                   /* next free position in buf */

struct tnode {
    char *word;
    int count;
    int lines[LINE_NUMBERS];
    struct tnode *left;
    struct tnode *right;
};

int getword(char *, int, int *);
struct tnode *addtree(struct tnode *, char *, int *);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char* strdpl(char *);

int main() {
    int nl;                                      /* new line */
    int lc;                                      /* line count */
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    nl = FALSE;
    lc = 1;

    while((getword(word,MAXWORD, &nl)) != EOF){
        if(isalpha(word[0]) && strlen(word) > MIN_LENGHT){
            root = addtree(root, word, &lc);
        }

        if(nl){
            lc++;
            nl = FALSE;
        }
    }

    treeprint(root);
    return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int *line){
    int cond;

    if(p == NULL) {
        p = talloc();
        p->count = 1;
        p->lines[p->count] = *line;
        p->word = strdpl(w);
        p->left = p->right = NULL;
    } else if((cond = strcmp(w, p->word)) == 0){
        p->count++;
        p->lines[p->count] = *line;
    } else if(cond < 0){
        p->left = addtree(p->left, w, line);
    } else {
        p->right = addtree(p->right, w, line);
    }

    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p){
    int i;
    if(p != NULL){
        treeprint(p->left);
        printf("%i ", p->count);
        printf("%s - ", p->word);
        for(i=1; i <= p->count; ++i){
            printf(" %i ", p->lines[i]);
        }
        printf("\n");
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
int getword(char *word, int lim, int *nl){
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
            *w = getch();

            if(*w == '\n'){
                *nl = TRUE;
            }

            if(!isalnum(*w)){
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