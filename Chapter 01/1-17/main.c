/**
 * Chapter: 1
 * Exercise: 1-17 - Write a program to print all input lines that are longer than 80 characters.
 **/

#include <stdio.h>

#define SIZE 80
#define MAXLINE 200

int read_line(char s[]);

int main() {
    int len;
    char line[MAXLINE];

    while ((len = read_line(line)) > 0){
        if(len > SIZE){
            printf("%s", line);
        }
    }

    return 0;
}

/* read_line: read a line into s, return length  */
int read_line(char s[]){
    int c, i;

    for(i=0; i<MAXLINE-1 && (c=getchar())!=EOF && c!='\n'; ++i){
        s[i] = c;
    }

    if(c == '\n'){
        s[i]=c;
        ++i;
    }

    s[i] = '\0';
    return i;
}