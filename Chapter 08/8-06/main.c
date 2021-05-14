/**
 * Chapter: 8
 * Exercise: 8-06 - The standard library function calloc(n,size) returns a pointer to n objects of size size, with the
 * storage initialized to zero. Write calloc, by calling malloc or by modifying it.
 **/

#include <stdio.h>

#define NALLOC      1024               /* minimum #units to request */

typedef long Align;                    /* for alignment to long boundary */

union header{                          /* block header: */
    struct{
        union header *ptr;             /* next block if on free list */
        unsigned size;                 /* size of this block */
    } s;
    Align x;                           /* force alignment of blocks */
};

typedef union header Header;

static Header base;                    /* empty list to get started */
static Header *freep = NULL;           /* start of free list */

void* malloc(unsigned);
static Header *morecore(unsigned);
void free(void *);
void* calloc(unsigned, unsigned);

int main() {
    int *p = (int *)calloc(1, sizeof(int));

    printf("Memory Address: %p\n", &p);
    printf("Value: %i\n", *p);

    return 0;
}

/* malloc: general-purpose storage allocator */
void* malloc(unsigned nbytes){
    Header *p, *prevp;
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;

    if ((prevp = freep) == NULL) {          /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
        if (p->s.size >= nunits) {
            if (p->s.size == nunits){
                prevp->s.ptr = p->s.ptr;
            } else {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }

            freep = prevp;
            return (void *) (p + 1);
        }

        if (p == freep) {                    /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL){
                return NULL;
            }
        }
    }
}

/* morecore: ask system for more memory */
static Header *morecore(unsigned nu) {
    char *cp;
    char *sbrk(int);
    Header *up;

    if (nu < NALLOC){
        nu = NALLOC;
    }

    cp = sbrk(nu * sizeof(Header));

    if (cp == (char *) -1){
        return NULL;
    }

    up = (Header *) cp;
    up->s.size = nu;
    free((void *)(up + 1));

    return freep;
}

/* free: put block ap in free list */
void free(void *ap) {
    Header *bp, *p;
    int valid;

    valid = 1;
    if (ap == NULL) {
        valid = 0;
    } else {
        bp = (Header *) ap - 1;
        if (bp->s.size <= 1) {
            valid = 0;
        }
    }

    if (valid) {
        for (p = freep ; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
            if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)){
                break;
            }

        if (bp + bp->s.size == p->s.ptr) {
            bp->s.size += p->s.ptr->s.size;
            bp->s.ptr = p->s.ptr->s.ptr;
        } else {
            bp->s.ptr = p->s.ptr;
        }

        if (p + p->s.size == bp) {
            p->s.size += bp->s.size;
            p->s.ptr = bp->s.ptr;
        } else {
            p->s.ptr = bp;
        }

        freep = p;
    }
}

/* calloc: general-purpose storage allocator. Initialize memory to zeros */
void* calloc(unsigned  n, unsigned size) {
    unsigned i, nb;
    char *p, *q;

    nb = n * size;

    if((p = q = malloc(nb)) != NULL){
        for(i=0; i<nb; i++){
            *p++ = 0;
        }
    }

    return q;
}