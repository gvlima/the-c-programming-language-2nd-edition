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
struct nlist* install(char *, char *);
void undef(char *);
void print_table(void);

static struct nlist *hashtab[HASHSIZE];     /* pointer table */

int main() {

    install("true", "1");
    install("false", "0");

    printf("### hashtab before undef ###\n");
    print_table();

    undef("false");

    printf("### hasbab after undef ####\n");
    print_table();

    return 0;
}

/* print_table: print hashtab table */
void print_table(void){
    for(int i=0; i<HASHSIZE; i++){
        if(hashtab[i] != NULL){
            printf("name: %s - defn: %s\n", hashtab[i]->name, hashtab[i]->defn);
        }
    }
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

/* undef: remove a name and definition from table */
void undef(char *s){
    int h;
    struct nlist *prev, *np;

    prev = NULL;

    h = hash(s);

    for(np = hashtab[h]; np != NULL; np = np->next){
        if(strcmp(s, np->name) == 0){
            break;
        }

        prev = np;
    }

    if(np != NULL) {
        if(prev == NULL) {
            hashtab[h] = np->next;
        } else {
            prev->next = np->next;
        }

        free((void *) np->name);
        free((void *) np->defn);
        free((void *) np);
    }
}
