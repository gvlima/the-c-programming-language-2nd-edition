/**
 * Chapter: 5
 * Exercise: 5-12 - Extend entab and detab to accept the shorthand entab -m + n to mean tab stops every n columns, starting
 * at column m. Choose convenient (for the user) default behavior.
 **/

#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}


int detab(int tabstop, int m) {
    int c, n, counter;

    n = counter = 0;
    while ((c = getchar()) != EOF) {
        if ((c != '\n' && c != '\t') && (counter >= m)) {
            ++n;;
            putchar(c);
        }
        if (c == '\t' && counter >= m)
            while (n++ < tabstop)
                putchar(' ');
        if (n >= tabstop || c == '\n')
            n = 0;
        if (c == '\n')
            counter = 0;
        if (counter < m) {
            counter++;
            putchar(c);
        }

    }
    putchar('\n');
    return 0;
}

void detab(int tabstop, int m){
    int c, blank, pos;
    pos = 1;

    while((c=getchar()) != EOF && c != '\n'){
        if(c == '\t'){
            blank = tabstop - ((pos - 1) % tabstop);
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