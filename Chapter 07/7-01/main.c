/**
 * Chapter: 7
 * Exercise: 7-01 - Write a program that converts upper case to lower or lower case to upper, depending on the name it is
 * invoked with, as found in argv[0].
 **/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int c;

    printf("%s\n", argv[0]);

    if(strcmp(argv[0], "./lower") == 0){
        while ((c=getchar()) != EOF){
            printf("%c", tolower(c));
        }
    } else if(strcmp(argv[0], "./upper") == 0){
        while ((c=getchar()) != EOF){
            printf("%c", toupper(c));
        }
    } else {
        printf("error: invalid invoked name.");
    }

    return 0;
}


/**
 * compile: gcc -o lower main.c and gcc -o upper main.c
 * usage: ./lower or ./upper
 **/