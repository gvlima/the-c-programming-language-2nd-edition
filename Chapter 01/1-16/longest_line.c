/**
 * Chapter: 1
 * Exercise: 1-16 - Revise the main routine of the longest-line program so it will correctly print the length of arbitrarily
 * long input lines, and as mush as possible of the text.
 **/

#include <stdio.h>

#define MAXLINE 1000 /* max input line size */

int read_line(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
    int len; /* current line length */
    int max; /* maximum length seen */
    char line[MAXLINE]; /* current input line */
    char longest[MAXLINE]; /* longest line saved */

    max = 0;
    while((len = read_line(line, MAXLINE)) > 0){
        if(len > max){
            max = len;
            copy(longest, line);
        }
    }
    if(max > 0) {
        printf("Length: %d | Line: %s", max, longest);
    }

    return 0;
}

/* read_line: read a line into s, return length  */
int read_line(char s[], int lim){
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

/* copy: copy 'from' into 'to', assume to is big enough */
void copy(char to[], char from[]){
    int i;

    i = 0;
    while((to[i] = from[i]) != '\0'){
        ++i;
    }
}

/**
 * Comment: The readline function receive two arguments, the first argument is an char array and is passed a memory address of array (call by reference),
 * the second argument is an integer and it makes a copy of value into function (call by value).
 **/