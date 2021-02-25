/**
 * Chapter: 1
 * Exercise: 1-24 - Write a program to check a C program for rudimentary syntax errors like unbalanced parentheses, brackets
 * and braces. Don't forget about quotes, both single and double, scape sequences, and comments. (This program is hard if you
 * do it in full generality).
 **/

#include <stdio.h>

#define IN 1
#define OUT 0

int in_comment();
int in_quotes();

int main() {
    int c, parentheses, brackets, braces, comment, quote;

    parentheses = brackets = braces = 0;

    while((c = getchar()) != EOF){
        if(c == '/'){
            if((c=getchar()) == '*'){
                comment = in_comment();
            }
        } else if(c == '\'' || c == '"'){
            quote = in_quotes();
        }

        if(parentheses < 0 || brackets < 0 || braces < 0){
            break;
        }

        if(c == '('){
            ++parentheses;
            continue;
        }

        if(c == ')'){
            --parentheses;
            continue;
        }

        if(c == "["){
            ++brackets;
            continue;
        }

        if(c == "]"){
            --brackets;
            continue;
        }

        if(c == "{"){
            ++braces;
            continue;
        }

        if(c == "}"){
            --braces;
            continue;
        }
    }

    if(parentheses != 0){
        printf("There are parentheses unbalanced.");
    }

    if(brackets != 0){
        printf("There are brackets unbalanced.");
    }

    if(braces != 0){
        printf("There are braces unbalanced.");
    }

    if(comment == IN){
        printf("There are open comment.");
    }

    if(quote == IN){
        printf("There are open quote.");
    }

    return 0;
}

int in_comment(){
    int c;

    c = getchar();

    while (c != EOF){
        if(c == '*'){
            if((c = getchar()) == '/'){
                return OUT;
            }
        }

        c = getchar();
    }

    return IN;
}

int in_quotes(){
    int c;

    while((c=getchar()) != EOF){
        if(c == '\'' || c == '"'){
            return OUT;
        }
    }

    return IN;
}