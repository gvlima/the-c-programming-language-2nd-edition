/**
 * Chapter: 5
 * Exercise: 5-11 - Modify the programs entab and detab (written as exercises in Chapter 1) to accept a list of tabs stops
 * as arguments. Use the default tab settings if there no arguments.
 **/

#include <stdio.h>
#define TABINC 8

int main(int argc, char* argv[]) {
    int c, blank, pos;
    pos = 1;

    while((c=getchar()) != EOF){
        if(c == '\t'){
            blank = TABINC - ((pos - 1) % TABINC);
            while(blank > 0){
                putchar('*');
                ++pos;
                --blank;
            }
        } else if( c == '\n') {
            putchar(c);
            pos = 1;
        } else {
            putchar(c);
            ++pos;
        }
    }
    return 0;
}
