/**
 * Chapter: 8
 * Exercise: 8-02 - Rewrite fopen and _fillbuf with fields instead of explicit bit operations. Compare code size and execution speed.
 **/

#include <fcntl.h>
#include <zconf.h>
#include <stdlib.h>
#include "systemcalls.h"

#define PERMS 0666

FILE* _fopen(char *, char *);
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;

    if(argc == 1){
        while ((c=getchar()) != _EOF){
            putchar(c);
        }
    } else {
        while(--argv > 0){
            if((fp == _fopen(*++argv, "r")) == _NULL){
                exit(EXIT_FAILURE);
            } else {
                while((c=getc(fp)) != EOF){
                    putchar(c);
                }
            }
        }
    }

    return 0;
}

/* fopen: open file, return file ptr */
FILE* _fopen(char *name, char *mode){
    int fd;
    FILE *fp;

    if(*mode != 'r' && *mode != 'w' && *mode != 'a'){
        return NULL;
    }

    for(fp = _iob; fp < _iob + OPEN_MAX; fp++){
        if(fp->flag._read == 0 && fp->flag._write == 0){
            break;
        }
    }

    if(fp >= _iob + OPEN_MAX){
        return NULL;
    }

    if(*mode == 'w'){
        fd = creat(name, PERMS);
    }else if(*mode == 'a'){
        if((fd = open(name, O_WRONLY, 0)) == -1){
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }

    if (fd == -1){
        return NULL;
    }

    fp->flag._buf = 1;
    fp->flag._unbuf = 0;
    fp->flag._eof = 0;
    fp->flag._err = 0;

    if(*mode == 'r'){
        fp->flag._read = 1;
        fp->flag._write = 0;
    } else {
        fp->flag._read = 0;
        fp->flag._write = 1;
    }

    return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp){
    int bufsize;

    if(fp->flag._read == 0){
        return EOF;
    }

    bufsize = (fp->flag._unbuf == 1) ? 1 : bufsize;

    if(fp->base == NULL){
        if((fp->base = (char *) malloc(bufsize)) == NULL){
            return EOF;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if(--fp->cnt < 0) {
        if(fp->cnt == -1){
            fp->flag._eof = 1;
        } else {
            fp->flag._err = 1;
        }

        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++;
}

/* _flushbuf: allocate and flush output buffer */
int _flushbuf(int x, FILE *fp) {
    int bufsize;

    if (fp->flag._write == 0) {
        return EOF;
    }

    bufsize = (fp->flag._unbuf == 1) ? BUFSIZ : 1;

    if (fp->base == NULL) {
        if ((fp->base = (char *) malloc(bufsize)) == _NULL) {
            return EOF;
        }
        *fp->base = '\0';
    }

    fp->ptr = fp->base;

    if(bufsize == 1){
        *fp->ptr = x;
    }

    if (*fp->ptr != '\0' || bufsize == 1) {
        fp->cnt = write(fp->fd, fp->ptr, bufsize);

        if (--fp->cnt != bufsize) {
            fp->flag._err = 1;
            fp->cnt = 0;
            return EOF;
        }
    }

    if (bufsize > 1) {
        *fp->ptr = x;
        fp->cnt = BUFSIZ - 1;
    }

    return (unsigned char) *fp->ptr++;
}

/* stdin, stdout, stderr */
FILE _iob[OPEN_MAX] = {
        { 0, (char *) 0, (char *) 0, {1, 0, 0 , 0, 0}, 0 },
        { 0, (char *) 0, (char *) 0, {0, 1, 0, 0, 0}, 1 },
        { 0, (char *) 0, (char *) 0, { 0, 1, 1, 0, 0} , 2 }
};
