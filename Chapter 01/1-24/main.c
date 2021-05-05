/**
 * Chapter: 1
 * Exercise: 1-24 - Write a program to check a C program for rudimentary syntax errors like unbalanced parentheses, brackets
 * and braces. Don't forget about quotes, both single and double, scape sequences, and comments. (This program is hard if you
 * do it in full generality).
 **/

#include <stdio.h>

void check_block_comment();
void skip_line_comment();
void check_single_quotes();
void check_double_quotes();
void check_syntax(int);

int status, brace, brackets, paren;

int main() {
    int c;

    status = 1;

    while ((c = getchar()) != EOF && status) {
        if (c == '/') {
            if ((c = getchar()) == '*') {
                check_block_comment();
            } else if (c == '/') {
                skip_line_comment();
            }
        } else if(c == '\''){
            check_single_quotes();
        } else if(c == '\"'){
            check_double_quotes();
        } else {
            check_syntax(c);
        }
    }

    if(brace != 0){
        printf("error: unbalanced braces.");
    } else if(brackets != 0){
        printf("error: unbalanced brackets.");
    } else if(paren != 0 ){
        printf("error: unbalanced parentheses.");
    }

    if(status){
        printf("there aren't errors.\n");
    } else {
        printf("there are syntax error.\n");
    }

    return 0;
}

/* check_syntax: verify unbalanced parentheses, brackets and braces  */
void check_syntax(int c){
    if(c == '{'){
        ++brace;
    } else if(c == '}') {
        --brace;
    } else if(c == '[') {
        ++brackets;
    } else if(c == ']') {
        --brackets;
    } else if(c == '(') {
        ++paren;
    } else if(c == ')') {
        --paren;
    }
}

/* check_block_comment: verify syntax for block comments */
void check_block_comment(){
    int prev_char, curr_char;

    prev_char = getchar();
    curr_char = getchar();

    while(prev_char != '*' || curr_char != '/'){
        if(curr_char == EOF){
            printf("there are syntax error in block comment.");
            status = 0;
            return;
        }

        prev_char = curr_char;
        curr_char = getchar();
    }
}

/* check_line_comment: verify syntax for line comment */
void skip_line_comment(){
    while (getchar() != '\n')
        ;
}

/* check_single_quotes: verify syntax for single quotes */
void check_single_quotes(){
    int c;

    while(c != '\''){
        if(c == EOF){
            printf("error: missing close single quote.");
            status = 0;
            return;
        }
        c = getchar();
    }
}

/* check_double_quotes: verify syntax for single quotes */
void check_double_quotes(){
    int c;

    while(c != '\"'){
        if(c == EOF){
            printf("error: missing close double quote.");
            status = 0;
            return;
        }

        c = getchar();
    }
}
