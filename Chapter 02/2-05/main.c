/**
 * Chapter: 2
 * Exercise: 2-05 - Write the function any(s1, s2), which returns the first location in the string s1 where any character
 * from the string s2 occurs, or -1 if s1 contains no characters from s2. (The standard library function strpbrk does the same
 * job but returns a pointer to the location.
 **/

#include <stdio.h>

#define MAX 100
#define NOTFOUND -1

int any(char s1[], char s2[]);

int main() {
    int location;
    char s1[MAX] = "abcdefghij";
    char s2[MAX] = "g";

    location = any(s1,s2);
    printf("Location: %i", location);
    return 0;
}

/* any: return the first location in the string where any char from s2 occurs */
int any(char s1[], char s2[]){
    int i, j, location;

    location = NOTFOUND;

    for(i=0; s2[i] != '\0'; i++){
        for(j=0; s1[j] != '\0'; j++){
            if(s1[j] == s2[i]){
                location = j;
                break;
            }
        }

        if(location != NOTFOUND){
            break;
        }
    }

    return location;
}