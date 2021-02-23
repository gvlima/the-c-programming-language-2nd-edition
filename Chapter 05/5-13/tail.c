/**
 * Chapter: 5
 * Exercise: 5-13 - Write the program tail, which prints the last n lines of its input. By default, n is 10, let us say,
 * but it can be changed by an optional argument, so that tail -n prints the last n lines. The program should behave rationally
 * no matter how unreasonable the input or the value of n. Write the program so it makes the best use of available storage;
 * lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of fixed size.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 100                              /* max length of an input line */
#define MAXLINES 10                             /* max number of lines to be sorted */
#define LINES 100                               /* max number of lines to print */
#define DEFAULT_N 10                            /* default number of lines to print */
#define ALLOCSIZE 10000                         /* size of available space */

static char allocbuf[ALLOCSIZE];                /* storage for alloc */
static char *allocp = allocbuf;                 /* next free position */
char* lineptr[MAXLINES];                        /* pointers to text lines */

int get_line(char s[], int lim);
char* alloc(int n);
int readlines(char* linesptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

int main(int argc, char* argv[]) {
    int n, nlines;

    if(argc == 1){
        n = DEFAULT_N;
    } else if(argc == 2 && (*++argv)[0] == '-') {
        n = atoi(argv[0]+1);
    } else {
        printf("error: unknown parameter");
    }

    if(n < 1 || n > LINES){                      /* check for unreasonable value for n */
        n = LINES;
    }

    nlines = readlines(lineptr, MAXLINES);

    if(nlines > 0){
        writelines(lineptr, n);
    } else {
        printf("there are no lines to print.");
    }

    return 0;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines){
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;

    while((len = get_line(line, MAXLEN)) > 1){
        if(nlines >= maxlines || (p = alloc(len)) == NULL){
            return -1;
        } else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines){
    while(nlines-- > 0){
        printf("%s\n", *lineptr++);
    }
}


/* get_line: read a line into s, return length  */
int get_line(char s[], int lim){
    int c, i;

    for(i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i){
        s[i] = c;
    }

    if(c == '\n'){
        s[i]=c;
        ++i;
    }

    s[i] = '\0';
    return i;
}

/* alloc: return a pointer to n character */
char* alloc(int n){
    if(allocbuf + ALLOCSIZE - allocp >= n){
        allocp += n;
        return allocp - n;
    } else {
        return 0;
    }
}

/* afree: free storage pointed to by p */
void afree(char *p) {
    if(p >= allocbuf && p < allocbuf + ALLOCSIZE){
        allocp = p;
    }
}