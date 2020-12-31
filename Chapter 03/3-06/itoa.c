/**
 * Chapter: 3
 * Exercise: 3-06 - Write a version of itoa that accepts three arguments instead of two. The third argument is a minimum
 * field width; The converted number must be padded with blanks on the left if necessary to make it wide enough.
 **/

#include <stdio.h>
#include <string.h>

void itoa(int n, char s[], int width);
void reverse(char s[]);

int main() {
    char s[20];
    itoa(54, s, 8);
    printf("%s\n", s);
    itoa(58674102, s, 8);
    printf("%s\n", s);
    return 0;
}

void itoa(int n, char s[], int width) {
    int i, sign = n;

    i = 0;
    do {
        int d = n % 10;
        if(sign < 0)
            d = -d;
        s[i++] = d + '0';
    } while((n /= 10) != 0);

    if(sign < 0) {
        s[i++] = '-';
        width--;
    }

    while(i < width) {
        s[i++] = ' ';
    }

    s[i] = '\0';

    reverse(s);
}

// Page 62
void reverse(char s[]) {
    int c, i, j;

    for(i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}