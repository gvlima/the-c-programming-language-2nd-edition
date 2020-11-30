/**
 * Chapter: 2
 * Exercise: 2-02 - Write a loop equivalent to the for loop above without using && or ||.
 **/

#include <stdio.h>

#define MAXLINE 100
#define TRUE 1
#define FALSE 0

int main() {
    char s[MAXLINE];
    int i, c, lim, valid;

    lim = MAXLINE;
    valid = TRUE;

    while(valid){
        c = getchar();

        if(i<lim-1){
            if(c != '\n'){
                if(c != EOF){
                    s[i]= c;
                    ++i;
                } else {
                    valid = FALSE;
                }
            } else {
                valid = FALSE;
            }
        } else {
            valid = FALSE;
        }
    }

    printf("%s", s);
    return 0;
}