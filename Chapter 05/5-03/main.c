/**
 * Chapter: 5
 * Exercise: 5-03 - Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s,t) copies the string
 * t to the end of s.
 **/

#include <stdio.h>

void strcat(char *, char *);

int main() {
    char s1[] = "text1";
    char s2[] = "text2";

    strcat(s1, s2);
    printf("%s", s1);

    return 0;
}

/* strcat: concatenate t to end of s; s must be big enough */
void strcat(char *s, char *t){
    int i, j;

    i = j = 0;

    while (*(s + i) != '\0') /* find end of s */
        i++;

    while ((*(s + i++) = *(t + j++)) != '\0') /* copy t */
        ;
}