/**
 * Chapter: 5
 * Exercise: 5-07 - Rewrite readlines to store lines in an array supplied by main, rather than calling alloc to maintain
 * storage. How much faster is the program?
 **/

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be stored */
#define MAXLEN 1000 /* max length of any input line */
#define ALLOC 10000

char* lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines, char *p);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);
int get_line(char*, int);

int main() {
    int nlines;
    char alloc_lines[ALLOC];

    if((nlines = readlines(lineptr, MAXLINES, alloc_lines)) > 0){
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Error: input too bit to sort.\n");
        return 1;
    }
}

/* get_line: read a line into s, return length */
int get_line(char *s, int lim){
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!= EOF && c != '\n'; ++i){
        *(s+i) = c;
    }

    if(c == '\n'){
        *(s+i) = c;
        ++i;
    }

    *(s+i) = '\0';

    return i;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char *alloc_lines){
    int len, nlines;
    char *p, line[MAXLEN];

    p = alloc_lines;
    nlines = 0;

    while((len = get_line(line, MAXLEN)) > 0){
        if(nlines >= maxlines || ((ALLOC + alloc_lines - p) < len)){
            return -1;
        } else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    }
    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines){
    while (nlines-- > 0){
        printf("%s\n", *lineptr++);
    }
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right){
    int i, last;
    void swap(char *v[], int i, int j);

    if(left >= right){
        return;
    }

    swap(v, left, (left + right) / 2);
    last = left;

    for(i = left+1; i <= right; i++){
        if(strcmp(v[i], v[left]) < 0){
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);

    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j){
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}