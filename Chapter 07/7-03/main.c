/**
 * Chapter: 7
 * Exercise: 7-03 - Revise mainprintf to handle more of the other facilities of printf.
 **/


#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

#define FORMAT_LEN 50

void minprintf(char *, ...);

int main() {
    int a = 10;
    double b = 20;
    char *text = "some text here";

    minprintf("integer: %i\n", a);
    minprintf("double: %f\n", b);
    minprintf("double with precision: %.2f\n", b);
    minprintf("string: %s\n", text);
    minprintf("hexadecimal: %x\n", a);

    return 0;
}

void minprintf(char *fmt, ...){
    char *p, *sval, format[FORMAT_LEN];
    int ival, i;
    double dval;
    unsigned uval;
    va_list ap;                         /* points to each unnamed arg in turn */

    va_start(ap, fmt);                  /* make ap point to 1st unnamed arg */

    for(p = fmt; *p; p++){
        if(*p != '%'){
            putchar(*p);
            continue;
        }

        i = 0;
        format[i++] = '%';
        while (*(p+1) && !isalpha(*(p+1))){
            format[i++] = *++p;
        }
        format[i++] = *(p+1);
        format[i] = '\0';

        switch (*++p){
            case 'i':
            case 'd':
                ival = va_arg(ap, int);
                printf(format, ival);
                break;
            case 'x':
            case 'X':
            case 'u':
            case 'o':
                uval = va_arg(ap, unsigned);
                printf(format, uval);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf(format, dval);
                break;
            case 's':
                for(sval = va_arg(ap, char *); *sval; sval++){
                    putchar(*sval);
                }
                break;
            default:
                putchar(*p);
                break;
        }
    }

    va_end(ap);                          /* clean up when done */
}