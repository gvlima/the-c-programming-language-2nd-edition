/**
 * Chapter: 3
 * Exercise: 3-01 - Our binary search makes two tests inside the loop, when one would suffice (at the price
 * of more tests outside). Write a version with only one test inside the loop and measure the difference in
 * run-time.
 **/

#include <stdio.h>
#include <time.h>

#define SIZE 100

int binsearch(int x, int v[], int n);
int binsearch_v1(int x, int v[], int n);

int main() {
    int v[SIZE], i, x, y;
    long t;

    x = 15;

    for(i=0; i<SIZE; ++i){
        v[i] = i;
    }

    t = clock();
    binsearch(x, v, SIZE);
    t = clock() - t;

    printf("run-time binsearch(): %ld\n", t);

    t = clock();
    binsearch_v1(x, v, SIZE);
    t = clock() - t;

    printf("run-time binsearch_v1(): %ld\n", t);

    return 0;
}

int binsearch(int x, int v[], int n){
    int low, high, mid;

    low = 0;
    high = n - 1;

    while (low <= high){
        mid = (low + high) / 2;

        if(x < v[mid]){
            high = mid - 1;
        } else if(x > v[mid]){
            low = mid + 1;
        } else { /* found match */
            return mid;
        }
    }

    return -1; /* no match */
}

int binsearch_v1(int x, int v[], int n){
    int low, high, mid;

    low = 0;
    high = n - 1;
    mid = (low + high) / 2;

    while (low <= high && x != v[mid]) {
        if(x < v[mid]){
            high = mid - 1;
        } else {
            low = mid + 1;
        }
        mid = (low + high) / 2;
    }

    if(x == v[mid]){
        return mid; /* found match */
    } else {
        return -1;  /* no match */
    }
}