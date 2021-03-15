/**
 * Chapter: 7
 * Exercise: 7-09 - Functions like issupper can be implemented to save space or to save time. Explore both possibilities.
 **/

#include <stdio.h>

#define issuper_v2(c) ((c) >= 'A' && (c) <= 'Z') ? 1 : 0

int issuper_v1(char c);

int main() {
    char letter = 'A';

    printf("issuper_v1(): %i\n", issuper_v1(letter));
    printf("issuper_v2(): %i\n", issuper_v2(letter));

    return 0;
}

/* issuper_v1: return 1 if c is an upper case latter */
int issuper_v1(char c){
    if(c >= 'A' && c <= 'Z'){
        return 1;
    } else {
        return 0;
    }
}

/**
 * issuper_v1 version save space.
 * issuper_v2 version save time (overhead of function call) but it uses more space because the macro
 * is expanded in line every time it is invoked.
 **/