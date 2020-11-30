/**
 * Chapter: 1
 * Exercise: 1-19 - Write a function reverse(s) that reverses the character string s. Use it to write a program that reverses
 * its input a line at time.
 **/

#include <stdio.h>

#define MAXLINE 200

int get_line(char s[], int limit);
void reverse(char s[], int limit);

int main() {
    char line[MAXLINE];
    int length;

    while ((length = get_line(line, MAXLINE)) > 0){
        reverse(line, length);
    }

    return 0;
}

/* reverse: print a string in reverse order */
void reverse(char s[], int length){
    int i;

    i=length;

    while (i > 0){
        printf("%c", s[i-1]);
        --i;
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