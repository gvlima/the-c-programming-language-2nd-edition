/**
 * Chapter: 1
 * Exercise: 1-22 - Write a program to "fold" long input lines into two or more shorter lines after the last non-blank character
 * that occurs before the n-th column of input. Make sure your program does something intelligent with very long lines, and if
 * there area no blanks or tabs before the specified column.
 **/

#include <stdio.h>

#define N 15
#define MAXLINE 50

char line[MAXLINE];
int pos;

print_line(char s[]);

int main() {
    int c, lb;
    extern int pos;
    extern char line[MAXLINE];

    pos = 0;
    lb = 0;

    while ((c=getchar()) != EOF){
        if((pos % N) != 0 || pos == 0){
            if(c == ' ' || c == '\t'){
                lb = pos;
            }

            line[pos] = c;
            ++pos;
        } else {
            if(lb != 0){
                line[lb] = '\n';
            } else {
                line[pos] = '\n';
                ++pos;
            }

            line[pos] = c;
            ++pos;
        }
    }

    print_line(line);
    return 0;
}

/* print_line: print entire line from string */
print_line(char s[]){
    int i;
    extern pos;

    for(i=0; i<pos; ++i){
        putchar(line[i]);
    }
}