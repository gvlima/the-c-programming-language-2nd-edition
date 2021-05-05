/**
 * Chapter: 5
 * Exercise: 5-15 - Add the option -f to fold upper and lower case together, so that case distinctions are not made during
 * sorting; for example, a and A compare equal.
 **/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 100                              /* max length of an input line */
#define MAXLINES 500                            /* max number lines to be sorted */
#define ALLOCSIZE 100000                        /* size of available space */
static char allocbuf[ALLOCSIZE];                /* storage for alloc */
static char *allocp = allocbuf;                 /* next free position */
char* lineptr[MAXLINES];                        /* pointers to text lines */
int numeric;                                    /* numeric sort, default is 0 */
int reverse;                                    /* sort in reverse order, default is 0 */
int fold;                                       /* case insensitive, default is 0 */

int get_line(char s[], int lim);
char* alloc(int n);
int readlines(char* lineptr[], int nlines);
void writelines(char* lineptr[], int nlines);
void qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
void swap(void* v[], int i, int j);
int numcmp(char *s1, char *s2);
int charcmp(char *s1, char *s2);
double atof(char s[]);

/* sort input lines */
int main(int argc, char *argv[]) {
    int nlines;                                 /* number of input lines read */

    numeric = 0;
    reverse = 0;
    fold = 0;

    for(int i=0; i < argc; i++){
        if(argc > 0 && (strcmp(argv[i], "-n") == 0)) {
            numeric = 1;
        }

        if(argc > 0 && (strcmp(argv[i], "-r") == 0)) {
            reverse = 1;
        }

        if(argc > 0 && (strcmp(argv[i], "-f") == 0)) {
            fold = 1;
        }
    }

    if((nlines = readlines(lineptr, MAXLINES)) >= 0){
        if(numeric){
            qsort((void **) lineptr, 0, nlines-1, (int (*)(void* , void*))numcmp);
        } else if(fold){
            qsort((void **) lineptr, 0, nlines-1, (int (*)(void* , void*))charcmp);
        } else {
            qsort((void **) lineptr, 0, nlines-1, (int (*)(void* , void*))strcmp);
        }

        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort.\n");
        return 1;
    }
}

/* charcmp: compare strings with case insensitive */
int charcmp(char *s1, char *s2){

    for(;*s1 == *s2;)
        ;

    return *s1 - *s2;
}

/* qsort: sort v[left]...v[right] in some order passed as argument */
void qsort(void *v[], int left, int right, int (*comp)(void *, void *)){
    int i, last;

    if(left >= right){
        return;
    }

    swap(v, left, (left + right/2));

    last = left;

    for(i = left+1; i<= right; i++){
        if(reverse){
            if((*comp)(v[i], v[left]) > 0){
                swap(v, ++last, i);
            }
        } else {
            if((*comp)(v[i], v[left]) < 0){
                swap(v, ++last, i);
            }
        }
    }

    swap(v, left, last);
    qsort(v, left, last-1, comp);
    qsort(v, last+1, right, comp);
}

/* atof: convert string s to double */
double atof(char s[]){
    double val, power;
    int exp, i, sign;

    for(i=0; isspace(s[i]); i++){
        ;
    }

    sign = (s[i] == '-') ? -1 : 1;

    if(s[i] == '+' || s[i] == '-'){
        i++;
    }

    for(val = 0.0; isdigit(s[i]); i++){
        val = 10.0 * val + (s[i] - '0');
    }

    if(s[i] == '.'){
        i++;
    }

    for(power = 1.0; isdigit(s[i]); i++){
        val  = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    val = sign * val / power;

    if(s[i] == 'e' || s[i] == 'E'){
        sign = (s[++i] == '-') ? -1 : 1;

        if(s[i] == '+' || s[i] == '-'){
            i++;
        }

        for(exp=0; isdigit(s[i]); i++){
            exp = 10 * exp + (s[i] - '0');
        }

        if(sign == 1){
            while (exp-- > 0){
                val *= 10;
            }
        } else {
            while (exp-- > 0){
                val /= 10;
            }
        }
    }

    return val;
}

/* swap: interchange v[i] and v[j] */
void swap(void* v[], int i, int j){
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2){
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if(v1 < v2){
        return -1;
    } else if (v1 > v2){
        return 1;
    } else {
        return 0;
    }
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
        printf("error: space for allocate.");
        return 0;
    }
}

/* afree: free storage pointed to by p */
void afree(char *p) {
    if(p >= allocbuf && p < allocbuf + ALLOCSIZE){
        allocp = p;
    }
}