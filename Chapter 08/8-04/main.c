/**
 * Chapter: 8
 * Exercise: 8-04 - The standard library function int fseek(FILE *fp, long offset, int origin) is identical to lseek except
 * that fp is a file pointer instead of a file descriptor and the return value is an int status, not a position. Write fseek.
 * Make sure that your fseek coordinates properly with the buffering done for the other function of the library.
 **/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "syscalls.h"

#define PERMS 0666

FILE _iob[OPEN_MAX] = {                /* stdin, stdout, stderr */
        { 0, (char *) 0, (char *) 0, _READ, 0 },
        { 0, (char *) 0, (char *) 0, _WRITE, 1 },
        { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

FILE *_fopen(char *, char *);
int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int fflush(FILE *);
int fclose (FILE *);
int fseek(FILE *, long, int);

int main(int argc, char *argv[]){
    FILE *fp;
    int c;

    if (argc == 1){
        while ((c = getchar()) != EOF){
            putchar(c);
        }
    } else {
        while (--argc > 0) {
            if ((fp = _fopen(*++argv, "r")) == NULL) {
                return 1;
            } else {
                while ((c = getc(fp)) != EOF) {
                    putchar(c);
                }

                fclose(fp);
            }
        }
    }

    if(ferror(stdout)){
        return 1;
    }

    fclose(stdout);
    return 0;
}

/* _fopen: open file, return ptr */
FILE *_fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++){
        if ((fp->flag & (_READ | _WRITE)) == 0){
            break;
        }
    }

    if ( fp >= _iob + OPEN_MAX){
        return NULL;

    }

    if (*mode == 'w'){
        fd = creat(name, PERMS);
    } else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1){
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    } else {
        fd = open(name, O_RDONLY, 0);
    }

    if (fd == -1){
        return NULL;
    }

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;

    return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp) {
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ){
        return EOF;
    }

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    if (fp->base == NULL){
        if ((fp->base = (char *) malloc(bufsize)) == NULL){
            return EOF;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = read(fileno(fp), fp->ptr, bufsize);

    if (--fp->cnt < 0) {
        if (fp->cnt == -1){
            fp->flag |= _EOF;
        } else {
            fp->flag |= _ERR;
        }

        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++;
}

/* _flushbuf: allocate and flush output buffer */
int _flushbuf(int x, FILE *fp) {
    int bufsize;

    if ((fp->flag & (_WRITE | _ERR)) != _WRITE){
        return EOF;
    }


    if (fp->flag & _UNBUF) {
        bufsize = 1;
    } else if (fp->flag & _EOF) {
        bufsize = BUFSIZ - fp->cnt;
    } else {
        bufsize = BUFSIZ;
    }

    if (fp->base == NULL) {
        if ((fp->base = (char *) malloc(bufsize)) == NULL){
            return EOF;
        }

        *fp->base = '\0';
    }

    fp->ptr = fp->base;

    if (bufsize == 1) {
        *fp->ptr = x;
    }

    if (*fp->ptr != '\0' || bufsize == 1) {
        fp->cnt = write(fileno(fp), fp->ptr, bufsize);

        if (fp->cnt != bufsize) {
            if (fp->cnt == -1) {
                fp->flag |= _EOF;
            } else {
                fp->flag |= _ERR;
            }

            fp->cnt = 0;
            return EOF;
        }
    }

    if (bufsize != 1) {
        *fp->ptr = x;
        fp->cnt = BUFSIZ - 1;
    }

    return (unsigned char) *fp->ptr++ ;
}

/* fflush: on output stream, write unwritten buffered data. On input stream,
 * the effect is undefined. NULL flushes all output streams. */
int fflush(FILE *fp) {
    FILE *cond;

    if (fp == NULL) {
        fp = _iob;
        cond = _iob + OPEN_MAX;
    } else {
        cond = fp + 1;
    }

    for (; fp < cond; fp++) {
        if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE){
            return EOF;
        }

        fp->flag |= _EOF;

        if (_flushbuf(*fp->ptr, fp) < 0){
            return EOF;
        }

        *fp->ptr = '\0';
        fp->cnt = 0;
    }
    return 0;
}

/* fclose: flushes unwritten date from stream, discard unread buffered input,
 * frees allocated memory, and closes stream. */
int fclose (FILE *fp) {
    if ((fp->flag & (_WRITE | _EOF | _ERR)) == _WRITE){
        if (fflush(fp) < 0){
            return EOF;
        }
    }

    free(fp->base);

    if (close(fileno(fp)) < 0) {
        fp->flag |= _ERR;
        return EOF;
    }

    return 0;
}