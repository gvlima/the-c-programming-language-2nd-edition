/**
 * Chapter: 1
 * Exercise: 1-23 - Write a program to remove all comments from a C program. Don't forget to handle quoted strings and
 * character constants properly. C comments do not nest.
 **/

#include <stdio.h>

#define OUT 0
#define IN 1

int status = OUT;

void remove_comment();

int main() {
    extern int status;
    int c, d;

    while ((c = getchar()) != EOF){

        if(c == '/'){
            d = getchar();
            if(d == '/'){
                while(getchar() != '\n'){
                }
            } else if(d == '*'){
                status = IN;
                remove_comment();
            } else {
                putchar(c);
                putchar(d);
            }
        } else {
            putchar(c);
        }

    }

    return 0;
}

void remove_comment(){
    extern int status;
    int c, d;

    c = getchar();
    d = getchar();

    while(status == IN){
        if(c == '*' && d == '/'){
            status = OUT;
        } else {
            c = d;
            d = getchar();
        }
    }
}