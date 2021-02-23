/**
 * Chapter: 5
 * Exercise: 5-12 - Extend entab and detab to accept the shorthand entab -m + n to mean tab stops every n columns, starting
 * at column m. Choose convenient (for the user) default behavior.
 **/

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_N 8
#define DEFAULT_M 1

void detab(int tabstop, int m);
void entab(int tabinc, int m);

int main(int argc, char *argv[]) {
    int pos, inc;

    if(argc <= 1){                                                      /* no parameters */
        pos = DEFAULT_M;
        inc = DEFAULT_N;
        printf("\nTesting detab with default values.\n");
    } else if(argc == 3 && *argv[1] == '-' && *argv[2] == '+') {        /* -m +n parameters */
        pos = atoi(argv[1]);
        inc = atoi(argv[2]);
        printf("\nTesting detab with provided parameters -m +n values.\n");
    } else if(argc == 2){                                               /* tab stop only */
        pos = atoi(argv[1]);
        printf("\nTesting detab with only tabstop value.\n");
    }

    detab(inc, pos);
    entab(inc, pos);

    return 0;
}


void detab(int tabstop, int m) {
    int c, blank, pos;
    pos = 1;

    while((c=getchar()) != EOF && c != '\n'){
        if(c == '\t' && pos > m) {
            blank = tabstop - ((pos - 1) % tabstop);
            while(blank > 0) {
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

void entab(int tabinc, int m){
    int c, pos, tab, blank;

    pos = 1; /* position count */
    tab = 0; /* tab count */
    blank = 0; /* blank space count */

    while((c=getchar()) != EOF && c != '\n'){
        if(c == ' ' && pos > m){
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

            if(c == '\t' && pos > m){
                blank = 0;
            } else {
                while(blank > 0){
                    putchar(' ');
                    --blank;
                }
            }

            putchar(c);

            if (c == '\t' && pos > m) {
                pos = pos + (tabinc - ((pos - 1) % tabinc)) - 1;
            }
        }

        ++pos;
    }
}
