/**
 * Chapter: 7
 * Exercise: 7-06 - Write a program to compare two files, printing the first line where they differ.
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 50

void compare(char *, char *, FILE *, FILE *);

int main(int argc, char *argv[]) {
    FILE *fp1, *fp2;
    char line1[MAX_LINE];
    char line2[MAX_LINE];

    if(argc != 3){
        printf("error: wrong args.");
        return 1;
    } else {
        if((fp1 = fopen(argv[1], "r")) == NULL){
            fprintf(stderr, "can't open file: %s\n", argv[1]);
            exit(1);
        }

        if((fp2 = fopen(argv[2], "r")) == NULL){
            fprintf(stderr, "can't open file: %s\n", argv[2]);
            exit(1);
        }

        compare(line1, line2, fp1, fp2);

        fclose(fp1);
        fclose(fp2);
    }

    return 0;
}

/* compare: print fist different line in two files */
void compare(char *line1, char *line2, FILE *fp1, FILE *fp2) {
    char *lp1, *lp2;

    do {
        if((lp1 = fgets(line1, MAX_LINE, fp1)) == NULL){
            printf("end file 01 at line: %s", line1);
        }

        if((lp2 = fgets(line2, MAX_LINE, fp2)) == NULL){
            printf("end file 02 at line: %s", line2);
        }

        if(lp1 != NULL && lp2 != NULL){
            if(strcmp(line1, line2) != 0){
                printf("at file 01 - line: %s", line1);
                printf("at file 02 - line: %s", line2);
                lp1 = lp2 = NULL;
            }
        }

    } while(lp1 != NULL && lp2 != NULL);
}

/**
 * comment: There are two files to test, pass they names as args.
 * usage: ./main "filename" "filename"
 * example: ./main "test_file1.txt" "test_file2.txt"
 **/