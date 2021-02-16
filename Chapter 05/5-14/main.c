/**
 * Chapter: 5
 * Exercise: 5-14 - Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing) order. Be
 * sure that -r works with -n.
 **/

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000               /* max #lines to be sorted */
#define MAXLEN 1000                 /* max length of any input line */
#define ALLOCSIZE 10000             /* size of available space */

char *lineptr[MAXLINES];            /* pointers to text lines */
static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;     /* next free position */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int get_line(char line[], int maxline);
int numcmp(char *, char *);
char* alloc(int n);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines;              /* number of input lines read */
    int numeric = 0;         /* 1 if a numeric sort */

    if(argc > 1 && strcmp(argv[1], "-n") == 0){
        numeric = 1;
    }

    if((nlines = readlines(lineptr, MAXLINES)) >= 0 ) {
        qsort((void **) lineptr, 0, nlines-1, (int (*)(void*, void*))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort.\n");
        return 1;
    }
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(void *v[], int left, int right, )){
    int i, last;

    void swap(void *v[], int, int);

    if(left >= right){
        return;
    }
    swap(v, left, (left + right)/2);
    last = left;

    for(i = left+1; i <= right; i++){
        if((*comp)(v[i], v[left]) < 0){
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort(v, left, last-1, comp);
    qsort(v, last+1, right, comp);
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines){
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;

    while((len = get_line(line, MAXLEN)) > 0){
        if(nlines >= maxlines || (p = alloc(len)) == NULL){
            return -1;
        } else {
            line[len-1] = '\0'; /* delete new line */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
}

/* alloc: return a point to n-consecutive char position */
char* alloc(int n){ /* has enough space */
    if(allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else { /* not enough space */
        return 0;
    }
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim){
    int c, i;

    for(i=0; i<lim-1 && (c=getchar() != EOF && c != '\n'); ++i){
        s[i] = c;
    }

    if(c == '\n'){
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines){
    while (nlines-- > 0){
        printf("%s\n", *lineptr++);
    }
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2){
    double v1, v2;

    v1 = 1;
    v2 = 2;

    if(v1 < v2) {
        return -1;
    } else if (v1 > v2){
        return 1;
    } else {
        return 0;
    }
}

/* swap: interchange v[i] and v[j] */
void swap(void *v[], int i, int j){
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}