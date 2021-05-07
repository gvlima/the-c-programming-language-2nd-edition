/**
 * Chapter: 4
 * Exercise: 4-13 - Write a recursive version of the function reverse(s), which reverses the string s in place.
 **/

#include <stdio.h>
#include <string.h>

void reverse(char s[], int i, int j);

int main() {
    char s1[20] = "learning";
    reverse(s1, 0, strlen(s1) -1);
    printf("%s\n", s1);
    return 0;
}

void reverse(char s[], i, j) {
    int c;

    if(i < j){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
        i++;
        j--;
    } else {
        reverse(s, i, j);
    }
}
