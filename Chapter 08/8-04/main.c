/**
 * Chapter: 8
 * Exercise: 8-04 - The standard library function int fseek(FILE *fp, long offset, int origin) is identical to lseek except
 * that fp is a file pointer instead of a file descriptor and the return value is an int status, not a position. Write fseek.
 * Make sure that your fseek coordinates properly with the buffering done for the other function of the library.
 **/

#include <zconf.h>
#include <fcntl.h>
#include "syscalls.h"
#include <stdio.h>

#define BUFSIZE 1

int fseek(FILE *, long, int);

int main() {
    FILE *fp;
    fp = fopen("teste.txt", "r");

    printf("%s", fp);

    return 0;
}


/* fseek: seek with a file pointer */
int fseek(FILE *fp, long offset, int origin){
    unsigned nc;
    long status = 0;

    if(fp->flag & _READ){
        if(origin == 1){
            offset -= fp->cnt;
        }

        status = lseek(fp->fd, offset, origin);

    } else if(fp->flag & _WRITE) {
        if((nc = fp->ptr - fp->base) > 0) {
            if(write(fp->fd, fp->base, nc) != nc){
                status = -1;
            }
        }

        if(status != -1){
            status = lseek(fp->fd, offset, origin);
        }
    }

    return (status == -1) ? -1 : 0;
}