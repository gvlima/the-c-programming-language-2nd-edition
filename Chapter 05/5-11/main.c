/**
 * Chapter: 5
 * Exercise: 5-11 - Modify the programs entab and detab (written as exercises in Chapter 1) to accept a list of tabs stops
 * as arguments. Use the default tab settings if there no arguments.
 **/

#include <stdio.h>
#include <stdlib.h>
#define TABINC 8

void detab(int);
void entab(int);

int main(int argc, char* argv[]) {

    if(argc > 1){
        for(int i=1; i < argc; i++){
            printf("\nTesting detab function TABSTOP = %s\n", argv[i]);
            detab(atoi(argv[i]));

            printf("\nTesting entab function TABSTOP = %s\n", argv[i]);
            entab(atoi(argv[i]));
        }
    } else {
        printf("\nTesting detab function TABSTOP = %i [default value]  \n", TABINC);
        detab(TABINC);

        printf("\nTesting entab function TABSTOP = %i [default value]  \n", TABINC);
        entab(TABINC);
    }

    return 0;
}

/* detab: replace tab in the input with proper number of blanks */
void detab(int tabinc){
    int c, blank, pos;
    pos = 1;

    while((c=getchar()) != EOF && c != '\n'){
        if(c == '\t'){
            blank = tabinc - ((pos - 1) % tabinc);
            while(blank > 0){
                putchar('#');
                ++pos;
                --blank;
            }
        } else {
            putchar(c);
            ++pos;
        }
    }
}

/* entab: replace a number of blanks by number of tabs */
void entab(int tabinc) {
    int c, pos, tab, blank;

    pos = 1; /* position count */
    tab = 0; /* tab count */
    blank = 0; /* blank space count */

    while((c=getchar()) != EOF && c != '\n'){
        if(c == ' '){
            if((pos % tabinc) != 0){
                ++blank;
            } else {
                blank = 0;
                ++tab;
            }
        } else {
            while(tab > 0){
                putchar('#');
                --tab;
            }

            if(c == '\t'){
                blank = 0;
            } else {
                while(blank > 0){
                    putchar('#');
                    --blank;
                }
            }

            putchar(c);

            if ( c == '\t') {
                pos = pos + (tabinc - ((pos - 1) % tabinc)) - 1;
            }
        }

        ++pos;
    }
}