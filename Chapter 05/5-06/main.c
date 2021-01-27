/**
 * Chapter: 5
 * Exercise: 5-06 - Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing.
 * Good possibilities include getline (Chapter 1 and 4), atoi, atoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3),
 * and strindex and getop (Chapter 4).
 **/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define BUFSIZE 100
#define NUMBER '0'  /* signal that a number was found */

char buf[BUFSIZE];  /* buffer for ungetch */
int  bufp = 0;      /* next free position in buf */
int getch(void);
void ungetch(int);
int get_line(char *, int lim);
int atoi(char *);
void itoa(int, char *);
void reverse(char *);
int strindex(char *, char *);
int getop(char *);

int main() {
    char s1[MAX];
    char s2[MAX];
    char s3[MAX] = "learning";
    char op[MAX];

    /* testing function atoi(char *) */
    get_line(s1, MAX);
    printf("get_line: %s\n", s1);

    /* testing function atoi(char *) */
    printf("atoi: %i\n", atoi("123s3a"));

    /* testing function itoa(int, char*) */
    itoa(1554, s2);
    printf("itoa: %s", s2);

    /* testing function reverse(char *) */
    reverse(s1);
    printf("reverse: %s", s1);

    /* testing function strindex(char *, char *) */
    printf("%i", strindex(s3, "rni"));

    /* testing function getop(char *) */
    if (getop(op) == NUMBER){
        printf("\nNumber was found: %s\n", op);
    } else {
        printf("\nAn operator or something else was found.\n");
    }

    return 0;
}

int getch(void) { /* get a (possibly pushed back) character */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
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

/* atoi: convert s to integer */
int atoi(char *s){
    int i, n, sign;

    for(i=0; isspace(*(s+i)); i++)
        ;

    sign = (*(s+i) == '-') ? -1 : 1;

    if(*(s+i) == '+' || *(s+i) == '-'){
      i++;
    }

    for(n = 0; isdigit(*(s+i)); i++){
        n = 10 * n + (*(s+i) - '0');
    }

    return sign * n;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[]){
    int sign = 1;

    if (n < 0){
        sign *= -1;
    }

    do {
        *s++ = sign*(n % 10) + '0';
    } while ((n /= 10) != 0);

    if (sign < 0){
        *s++ = '-';
    }
    *s = '\0';
}

/* reverse: reverse string s in place */
void reverse(char *s){
    int c, i, j;

    for(i = 0, j = strlen(s)-1; i < j; i++, j--){
        c = *(s+i);
        *(s+i) = *(s+j);
        *(s+j) = c;
    }
}

/* strindex: return index of t in s, -1 if none */
int strindex(char *s, char *t){
    int i, j, k;

    for(i = 0; *(s+i) != '\0'; i++){

        for(j=i, k=0; *(t+k) != '\0' && *(s+j) == *(t+k); j++, k++)
            ;

        if(k > 0 && *(t+k) == '\0'){
            return i;
        }
    }
    return -1;
}

/* getop: get next operator or numeric operand */
int getop(char s[]){
    int i, c;

    while((*s = c = getch()) == ' ' || c == '\t')
        ;

    *(s+1) = '\0';

    if(!isdigit(c) && c != '.'){
        return c; /* not a number */
    }

    i = 0;

    if(isdigit(c)){ /* collect integer part */
        while (isdigit(*(s+i) = c = getch())){
            ++i;
        }
    }

    if(c == '.'){ /* collect fraction part */
        while (isdigit(*(s+i) = c = getch())){
            ++i;
        }
    }

    *(s+i) = '\0';

    if(c != EOF){
        ungetch(c);
    }

    return NUMBER;
}
