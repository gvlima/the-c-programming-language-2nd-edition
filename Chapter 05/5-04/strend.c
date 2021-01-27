/**
 * Chapter: 5
 * Exercise: 5-04 - Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s,
 * and zero otherwise.
 **/

#include <stdio.h>
#include <string.h>

int strend(char *, char *);

int main() {
    char s1[] = "another text";
    char s2[] = "text";

    printf("%i",  strend(s1, s2));

    return 0;
}

int strend(char *s, char *t){
    int i, p;

    i = 0;
    p = strlen(s) - strlen(t);

    while(*(s+p) != '\0'){
      if(*(s + p++) != *(t + i++)){
          return 0;
      }
    }

    return 1;
}