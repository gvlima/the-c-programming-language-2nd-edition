/**
 * Chapter: 7
 * Exercise: 7-04 - Write a private version of scanf analogous to minprintf from the previous sections.
 **/

#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

#define FORMAT_LEN 50

int minscanf(char*, ...);

int main() {
    int x;

    minscanf("%i", &x);
    printf("x = %i", x);

    return 0;
}

int minscanf(char *fmt, ...){
    int i, *ival;
    char *p, *sval, format[FORMAT_LEN];
    unsigned *uval;
    double *dval;
    va_list ap;

    i = 0;                                       /* index for format array */
    va_start(ap, fmt);                           /* make ap point to 1st unnamed arg */

    for(p = fmt; *p; p++){
        if(*p != '%'){
            format[i++] = *p;                    /* collect chars */
            continue;
        }

        format[i++] = '%';                       /* start format */

        while (*(p+1) && !isalpha(*(p+1))){
            format[i++] = *++p;                  /* collect chars */
        }

        format[i++] = *(p+1);
        format[i] = '\0';

        switch (*++p){
            case 'i':
            case 'd':
                ival = va_arg(ap, int *);
                scanf(format, ival);
                break;
            case 'x':
            case 'X':
            case 'u':
            case 'o':
                uval = va_arg(ap, unsigned *);
                scanf(format, uval);
                break;
            case 'f':
                dval = va_arg(ap, double *);
                scanf(format, dval);
                break;
            case 's':
                sval = va_arg(ap, char *);
                scanf(format, sval);
                break;
            default:
                scanf(format);
                break;
        }

        i=0;                                     /* reset index */
    }

    va_end(ap);                                  /* clean up when done */
}