#include <stdio.h>
#define LEN 100

int main() {
    int c, i;
    char s[LEN], t[LEN];

    i = 0;

    while((c = getchar()) != EOF){
        s[i] = c;
        ++i;
    }

    printf("%s", s);

    return 0;
}