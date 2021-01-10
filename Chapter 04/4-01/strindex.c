/**
 * Chapter: 4
 * Exercise: 4-01 - Write the function strrindex(s,t), which returns the position of the righmost occurrence of t in s,
 * or -1 if there is none.
 **/

#include <stdio.h>

#define MAXLINE 1000

int get_line(char line[], int max);
int strrindex(char source[], char searchfor[]);
char pattern[] = "ould";

int main() {
    char line[MAXLINE];
    int found = 0;

    while(get_line(line, MAXLINE) > 0){
        if(strrindex(line, pattern) >= 0){
            printf("%s", line);
            found++;
        }
    }

    return 0;
}

/* get_line: get line into s, return length */
int get_line(char s[], int lim){
    int c, i;

    i = 0;
    while(--lim > 0 && (c=getchar()) != EOF && c != '\n'){
        s[i++] = c;
    }

    if(c == '\n'){
        s[i++] = c;
    }

    s[i] = '\0';

    return i;
}

/* strrindex: return index of t in s, =1 if none */
int strrindex(char s[], char t[]){
    int i, j, k, p;

    p = -1;

    for (i=0; s[i] != '\0'; i++){
        for(j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++){
        }

        if(k > 0 && t[k] == '\0'){
            p = i;
        }

    }

    return p;
}