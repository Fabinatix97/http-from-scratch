#include <stdio.h>
#include <stdlib.h>

int G = 0;

int main() {
    static int s;
    int a;
    int b = 42;
    int *p;
    int *q = &b;

    p = malloc(sizeof(int));

    printf("&G   = %p\n", (void *) &G);
    printf("G    = %d\n", G);
    printf("&s   = %p\n", (void *) &s);
    printf("s    = %d\n", s);
    printf("&a   = %p\n", (void *) &a);
    printf("a    = %d\n", a);
    printf("&b   = %p\n", (void *) &b);
    printf("b    = %d\n", b);
    printf("&p   = %p\n", (void *) &p);
    printf("*p   = %p\n", (void *) p);
    printf("p    = %d\n", *p);
    printf("&q   = %p\n", (void *) &q);
    printf("*q   = %p\n", (void *) q);
    printf("q    = %d\n", *q);

    free(p);

    return 0;
}
