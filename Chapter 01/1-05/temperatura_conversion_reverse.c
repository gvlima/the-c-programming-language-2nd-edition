/**
 * Chapter: 1
 * Exercise: 1-5 - Modify the temperature conversion program to print the table in reverse order, that is, from 300 to 0.
 **/

#include <stdio.h>

int main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("Fahrenheit Celsius\n");
    for(fahr = upper; fahr >= lower; fahr = fahr - step){
        celsius = (5.0/9.0) * (fahr-32.0);
        printf("%3.0f \t %6.1f\n", fahr, celsius);
    }

    return 0;
}

/**
 *  Note: Using for statement to control loop, the variable initialization and increment are made in header of for loop.
 **/