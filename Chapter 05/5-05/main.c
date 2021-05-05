/**
 * Chapter: 5
 * Exercise: 5-05 - Write version of the library functions strncpy, strncat, and strncmp, which operate on at most the first
 * n characters of their argument strings. For exemple, strncpy(s, t, n) copies at most n characters of t to s. Full description
 * are in Appendix B.
 **/

#include <stdio.h>

void strncpy(char *, char *, int);
void strncat(char *, char *, int);
int strncmp(char *, char *, int);

int main() {
    char s1[] = "text";
    char s2[] = "another text";
    char s3[] = "text";
    char s4[] = "text 2";

    // test strncat function
    strncat(s1, s2, 5);
    printf("strncat: %s", s1);

    // test strncmp
    printf("strncmp: %i", strncmp(s3, s4, 2));

    // test strncpy
    strncpy(s3, s4, 3);
    printf("strncpy: %s", s3);

    return 0;
}

/* strcat: concatenate t to end of s; s must be big enough */
void strncat(char *s, char *t, int n){
    int i, j;

    i = j = 0;

    while (*(s + i) != '\0') /* find end of s */
        i++;

    while(n > 0){
        *(s + i++) = *(t + j++);
        n--;
    }

    *(s + i) = '\0';
}

/* strncmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int strncmp(char *s, char *t, int n){
    for( ; *s == *t && n > 0; s++, t++, n--){
        if(*s == '\0'){
            return 0;
        }
    }

    return *s - *t;
}

/* strncpy: copy t to s */
void strncpy(char *s, char *t, int n){

    while(n-- > 0 && (*s++ = *t++) != '\0')
        ;

    *s = '\0';
}