/**
 * Chapter: 1
 * Exercise: 1-6 - Verify that the expression getchar() != EOF is 0 or 1.
 **/

#include <stdio.h>

int main() {
    int c;
    while (c = getchar() != EOF){
        printf("%i\n", c);
    }
    printf("%i", c);
    return 0;
}

/**
 * Comment: Equality operation has higher precedence than the assignment operator, so the expression getchar() != EOF
 * is evaluated first, then the result of this evaluation is assigned to variable c instead the data read from getchar().
 **/
