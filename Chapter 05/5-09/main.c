/**
 * Chapter: 5
 * Exercise: 5-09 - Rewrite the routines day_of_year and month_day with pointers instead of indexing.
 **/

#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pda);

static char daytab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main() {
    int month, day, year, yearday;

    year = 2021;
    month = 2;
    day = 5;

    // testing function day_of_year
    yearday = day_of_year(year, month, day);
    if(yearday > 0){
        printf("2021/2/5 is day %i of year.\n", yearday);
    }

    // testing function month_year;
    yearday = 37;
    month_day(year, yearday, &month, &day);
    if(month > 1 && day > 1 && year > 1){
        printf("the day %i of year is %i/%i/%i.\n", yearday, year, month, day);
    }

    return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day){
    int i, leap;

    // check if is a valid year
    if(year < 1){
        printf("Invalid year.\n");
        return -1;
    }

    leap = (year % 4 == 0) && (year % 100) != 0 || year % 400 == 0;

    // check if is a valid month
    if(month < 1 || month > 12){
        printf("Invalid month.\n");
        return -1;
    }

    // check if is a valid day
    if(day < 1 || day > *(*(daytab + leap) + month)){
        printf("Invalid day.\n");
        return -1;
    }

    for(i = 1; i< month; i++){
        day += *(*(daytab + leap) + i);
    }

    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday){
    int i, leap;

    // check if is a valid year
    if(year < 0){
        *pmonth = -1;
        *pday = -1;
        return;
    }

    leap = (year % 4 == 0) && (year % 100) != 0 || year % 400 == 0;

    for(i = 1; yearday > *(*(daytab + leap) + i); i++){
        yearday -= *(*(daytab + leap) + i);
    }

    if(i > 12 && yearday > *(*(daytab + leap) + 12)){
        *pmonth = -1;
        *pday = -1;
    } else {
        *pmonth = i;
        *pday = yearday;
    }

}