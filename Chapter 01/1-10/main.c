/**
 * Chapter: 1
 * Exercise: 1-10 - Write a program to copy its input to its output, replacing each tab by \t, each backspace by \b, and
 * each backslash by \\. This makes tabs and backspaces visible in an unambiguous way.
 */

#include <stdio.h>

int main() {
    int c;

    while ((c = getchar()) != EOF){
        if(c == '\t'){
            printf("\\t");
        } else if (c == ' '){
            printf("\\b");
        } else if (c == '\\'){
            printf("\\\\");
        } else {
            putchar(c);
        }
    }

    return 0;
}

/**
 * Comment: A character written between single quotes represents an integer value equal to the numerical value of the machine's
 *  character set (ASCII).
 **/