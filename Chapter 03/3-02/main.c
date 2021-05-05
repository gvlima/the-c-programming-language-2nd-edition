/**
 * Chapter: 3
 * Exercise: 3-02 - Write a function escape(s,t) that converts characters like newline and tab into visible escape sequences like
 * \n and \t as it copies the string t to s. Use a switch. Write a function for the other direction as well, converting escape
 * sequences into the real characters.
 **/

#include <stdio.h>
#define LEN 100

void escape(char s[], char t[]);
void unscape(char s[], char t[]);

int main() {
    int c, i=0;
    char s[LEN], t[LEN];

    while((c = getchar()) != EOF){
        t[i] = c;
        ++i;
    }

    escape(s, t);
    //unscape(s, t);
    printf("%s", s);

    return 0;
}

/* escape: convert scape characters into visible scape sequences */
void escape(char s[], char t[]){
    int i, j;

    for(i=j=0; i<LEN && t[i] != '\0'; i++){
        switch(t[i]){
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            default:
                s[j++] = t[i];
                break;
        }
    }
}

/* unescape: convert visible scape sequences into scape characters  */
void unscape(char s[], char t[]){
    int i, j;

    for(i=j=0; i<LEN && t[i] != '\0'; i++){
        if(t[i] == '\\'){
            switch(t[++i]){
                case 't':
                    s[j++] =  '\t';
                    break;
                case 'n':
                    s[j++] = '\n';
                    break;
                default:
                    s[j++] = t[i];
                    break;
            }
        } else {
            s[j++] = t[i];
        }
    }
}