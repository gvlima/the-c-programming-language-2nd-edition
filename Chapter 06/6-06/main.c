/**
 * Chapter: 6
 * Exercise: 6-06 - Implement a simple version of the #define processor (i.e., no arguments) suitable for use with C programs,
 * based on the routines of this section. You may also find getch and ungetch helpful.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASHSIZE 101
#define MAXWORD 100
#define BUFSIZE 1000

char buf[BUFSIZE];                              /* buffer for ungetch */
int bufp = 0;                                   /* next free position in buf */

struct nlist {                                  /* table entry */
    struct nlist *next;                         /* next entry in chain */
    char *name;                                 /* defined name */
    char *defn;                                 /* replacement text */
};

static struct nlist *hashtab[HASHSIZE];         /* pointer table */

unsigned hash(char *);
struct nlist *lookup(char *s);
struct nlist* install(char *, char *);
int getword(char *, int);
getch(void);
void ungetch(int);
void print_table(void);

int main(){
    char word[MAXWORD];
    char defn[MAXWORD];
    const char *KEYWORK = "#define";

    while((getword(word, MAXWORD)) != EOF){
        if(word[0] == '#' && (strcmp(word, KEYWORK) == 0)){
           getword(word, MAXWORD);
           getword(defn, MAXWORD);
           install(word,defn);
        }
    }

    print_table();

    return 0;
}

/* hash: form hash value for string s */
unsigned hash(char *s){
    unsigned hashval;

    for(hashval = 0; *s != '\0'; s++){
        hashval = *s + 31 * hashval;
    }

    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s){
    struct nlist *np;

    for(np = hashtab[hash(s)]; np != NULL; np = np->next){
        if(strcmp(s, np->name) == 0){
            return np;                      /* found */
        }
    }

    return NULL;                            /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist* install(char *name, char *defn){
    struct nlist *np;
    unsigned hashval;

    if((np = lookup(name)) == NULL){
        np = (struct nlist *) malloc(sizeof(*np));

        if(np == NULL || (np->name = strdup(name)) == NULL){
            return NULL;
        }

        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *) np->defn);
    }

    if((np->defn = strdup(defn)) == NULL){
        return NULL;
    }

    return np;
}


/* getword: get next word of character from input */
int getword(char *word, int lim){
  int c;
  char *w = word;

  while(isspace(c = getch())){
  }

  if(c != EOF){
      *w++ = c;
  }

  if (isalpha(c) || c == '_' || c == '#') {
      for ( ; --lim > 0; ++w) {
          if (!isalnum(*w = getch()) && *w != '_') {
              ungetch(*w);
              break;
          }
      }
  } else if (c == '\''){
      while ((c = getch()) != '\'')
          ;
  } else if (c == '\"'){
      while ((c = getch()) != '\"')
          if (c == '\\'){
              getch();
          }
  } else if (c == '/' && (c = getch()) == '*'){
      while ((c = getch()) != EOF){
          if (c == '*' && (c = getch()) == '/'){
              break;
          }
      }
  }

  *w ='\0';
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

/* print_table: print hashtab table */
void print_table(void){
    for(int i=0; i<HASHSIZE; i++){
        if(hashtab[i] != NULL){
            printf("name: %s - defn: %s\n", hashtab[i]->name, hashtab[i]->defn);
        }
    }
}