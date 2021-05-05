/**
 * Chapter: 1
 * Exercise: 1-18 - Write a program to remove trailing blanks and tabs from each line of input, and to delete entirely blank lines.
 **/

#include <stdio.h>

#define MAXLINE 500
#define IN 1                        /* inside a word */
#define OUT 0                       /* outside a word */

int read_line(char s[], int limit);
int remove_blanks(char s[], int limit);

int main() {
    char line[MAXLINE];

    while (read_line(line, MAXLINE) > 0){
        if((remove_blanks(line, MAXLINE)) > 0 && line[0]!='\n'){
            printf("%s", line);
        }
    }

    return 0;
}

/* remove blanks: remove blank space */
int remove_blanks(char s[], int limit){
    int i, j, status;

    j = 0;
    status = OUT;

    for(i=0; i<limit-1 && s[i] && s[i] != EOF; ++i){
        if(s[i] != ' ' && s[i] != '\t'){
            status = IN;
            s[j]=s[i];
            ++j;
        } else if((s[i] == ' ' || s[i] == '\t') && status == IN){
            status = OUT;
            s[j]=s[i];
            ++j;
        }
    }

    s[j]=s[i];
    return j;
}

/* read_line: read a line into s, return length  */
int read_line(char s[], int lim){
    int c, i;

    for(i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i){
        s[i] = c;
    }

    if(c == '\n'){
        s[i]=c;
        ++i;
    }

    s[i] = '\0';
    return i;
}
