/**
 * Chapter: 7
 * Exercise: 7-07 - Modify the pattern finding program of Chapter 5 to take its input from a set of named files or, if no
 * files are named as arguments, from the standard input. Should the file name be printed when a matching line is found?
 **/

#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int main(int argc, char *argv[]) {
    FILE *fp;
    char line[MAXLINE];
    int c, except, number, found;
    long lnum;

    c = except = number = found = 0;
    lnum = 0;

    if(argc < 3) {
        printf("Usage: find filename.txt pattern -x -n.\n");
    } else {
        while (--argc > 0 && (*++argv)[0] == '-') {
            while (c = *++argv[0]){
                switch (c){
                    case 'x':
                        except = 1;
                        break;
                    case 'n':
                        number = 1;
                        break;
                    default:
                        printf("find: illegal option %c\n", c);
                        argc = 0;
                        found = -1;
                        break;
                }
            }
        }

        if((fp = fopen(*argv++, "r")) == NULL) {
            fprintf(stderr, "can't open file: %s", *argv);
        } else {
            while (fgets(line, MAXLINE, fp) != NULL) {
                ++lnum;

                if((strstr(line, *argv) != NULL) != except) {
                    if(number){
                        printf("%ld: ", lnum);
                    }
                    printf("%s", line);
                    found++;
                }
            }
        }
    }

    return found;
}