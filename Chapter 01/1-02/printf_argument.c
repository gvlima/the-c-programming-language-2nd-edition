/**
 * Chapter: 1
 * Exercise: 1-2 - Experiment to find out what happens when printf's argument string contains \c, where is some character not listed above.
 **/

#include <stdio.h>

int main() {
    printf("Hello, World!\c");
    return 0;
}

/**
 * Comment: The C compiler not recognize '\c' as an escape sequence and throws a warning during compile but print the letter without backslash.
 **/