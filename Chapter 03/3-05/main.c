/**
 * Chapter: 3
 * Exercise: 3-05 - Write the function itob(n,s,b) that converts the integer n into a base b character representation
 * in the string s. In particular, itob(n,s,16( formats n as a hexadecimal integer in s.
 **/

#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b);
void reverse(char s[]);

int main() {
    int n = 4, b = 2;
    char s[20];

    itob(n, s, b);
    printf("%i in base %i is %s\n", n, b, s);

    return 0;
}

/* itob: convert n characters into a base b in s */
void itob(int n, char s[], int b) {
    int i, sign = n;

    i = 0;

    do {
        int d = n % b;

        if(sign < 0) {
            d = -d;
        }

        if(d <= 9) {
            s[i++] = d + '0';
        } else {
            s[i++] = d - 10 + 'A';
        }
    } while((n /= b) != 0);

    if(sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}

/* reverse: reverse string s in place (at page 62) */
void reverse(char s[]) {
    int c, i, j;

    for(i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
