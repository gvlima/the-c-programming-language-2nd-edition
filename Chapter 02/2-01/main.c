/**
 * Chapter: 2
 * Exercise: 2-1 - Write a program to determine the range of char, short, int and long variables, both signed and unsigned,
 * by printing appropriate values from standard headers and by direct computation. Header if you compute them: determine the
 * ranges of the various floating-point types.
 **/

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    printf("##### Values from direct computation #####\n");
    printf("### char ###\n");
    printf("signed char min: %d\n",-(char)((unsigned char) ~0 >> 1));
    printf("signed char max: %d\n",(char)((unsigned char) ~0 >> 1));
    printf("unsigned char max: %u\n",((unsigned char) ~0));

    printf("###  short ###\n");
    printf("signed short min: %d\n",-(short)((unsigned short) ~0 >> 1));
    printf("signed short max: %d\n",(short)((unsigned short) ~0 >> 1));
    printf("unsigned short max: %u\n",((unsigned short) ~0));

    printf("### int ###\n");
    printf("signed int min: %d\n",-(int)((unsigned int) ~0 >> 1));
    printf("signed int max: %d\n",(int)((unsigned int) ~0 >> 1));
    printf("unsigned int max: %u\n",((unsigned int) ~0));

    printf("### long ###\n");
    printf("signed long min: %ld\n",-(long)((unsigned long) ~0 >> 1));
    printf("signed long max: %ld\n",(long)((unsigned long) ~0 >> 1));
    printf("unsigned long max: %lu\n",((unsigned long) ~0));

    printf("\n");

    printf("##### Values from header <limits.h> #####\n");
    printf("### char ###\n");
    printf("signed char min: %d\n", SCHAR_MIN);
    printf("signed char max: %d\n", SCHAR_MAX);
    printf("unsinged char max: %u\n", UCHAR_MAX);
    printf("### short ###\n");
    printf("signed short min: %d\n", SHRT_MIN);
    printf("signed short max: %d\n", SHRT_MAX);
    printf("unsigned short max: %u\n", USHRT_MAX);
    printf("### int ###\n");
    printf("signed int min: %d\n", INT_MIN);
    printf("signed int max: %d\n", INT_MAX);
    printf("unsigned int max: %u\n", UINT_MAX);
    printf("### long ###\n");
    printf("signed long min: %ld\n", LONG_MIN);
    printf("signed long max: %ld\n", LONG_MAX);
    printf("unsigned long max: %lu\n", ULONG_MAX);

    printf("##### Values from header <float.h> #####\n");
    printf("### single float-point ###\n");
    printf("float min: %E\n", FLT_MIN);
    printf("float max: %E\n", FLT_MAX);

    printf("### double float-point ###\n");
    printf("double min: %E\n", DBL_MIN);
    printf("double max: %E\n", DBL_MAX);

    printf("### long double float-point ###\n");
    printf("long double min: %LE\n", LDBL_MIN);
    printf("long double max: %LE\n", LDBL_MAX);

    return 0;
}