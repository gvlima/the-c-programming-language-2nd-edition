/**
 * Chapter: 6
 * Exercise: 6-05 - Write a function undef that will remove a name and definition from the table maintained by lookup
 * and install.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101

struct nlist {                              /* table entry */
    struct nlist *next;                     /* next entry in chain */
    char *name;                             /* defined name */
    char *defn;                             /* replacement text */
};

unsigned hash(char *);
struct nlist* lookup(char *);

static struct nlist *hashtab[HASHSIZE];     /* pointer table */

int main() {
    printf("Hello, World!\n");
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
    }
}