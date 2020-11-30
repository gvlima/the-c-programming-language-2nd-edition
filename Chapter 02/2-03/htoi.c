/**
 * Chapter: 2
 * Exercise: 2-03 - Write the function htoi(s), witch converts a string of hexadecimal digits (including an optional 0x or 0X) into
 * its equivalent integer value. The allowable digits are 0 through 9, a through f and A though F.
 **/

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX 10

int htoi(char s[MAX]);

int main() {
    int value;
    char hex[MAX] = {"0x11a"};

    value = htoi(hex);

    printf("hex: %s, dec: %i", hex, value);
    return 0;
}

int htoi(char s[]){
    int i, value, len;

    value = 0;
    len = strlen(s);

    if(s[i] == '0'){ /* skip prefix 0x or 0X */
        ++i;
        if(s[i] == 'x' || s[i] == 'X'){
            ++i;
        }
    }

    for(i; s[i] != '\0'; ++i){
        if(s[i] >= 'A' && s[i] <= 'F') {
            value += (s[i]-55) * pow(16, (len-1)-i);
        }

        if(s[i] >= 'a' && s[i] <= 'f'){
            value += (s[i]-87) * pow(16, (len-1)-i);
        }

        if(s[i] >= '0' && s[i] <= '9'){
            value += (s[i]-48) * pow(16, (len-1)-i);
        }
    }

    return value;
}