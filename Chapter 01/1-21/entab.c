/**
 * Chapter: 1
 * Exercise: 1-21 - Write a program entab that replaces strings of blanks by the minimum number of tabs and blanks to archive the same spacing.
 * Use the same tab stops as for detab. When either a tab or a single blank would suffice to reach a tab stop, witch should be given preference?
 **/

#include <stdio.h>

#define TABINC 8 /* tab size */

int main() {
    int c, pos, tab, blank;

    pos = 1; /* position count */
    tab = 0; /* tab count */
    blank = 0; /* blank space count */

    while((c=getchar()) != EOF){
        if(c == ' '){
            if((pos % TABINC) != 0){
                ++blank;
            } else {
                blank = 0;
                ++tab;
            }
        } else {
            while(tab > 0){
                putchar('*');
                --tab;
            }

            if(c == '\t'){
                blank = 0;
            } else {
                while(blank > 0){
                    putchar(' ');
                    --blank;
                }
            }

            putchar(c);

            if(c == '\n') {
                pos = 0;
            } else if ( c == '\t') {
                pos = pos + (TABINC - ((pos - 1) % TABINC)) - 1;
            }
        }

        ++pos;
    }

    return 0;
}