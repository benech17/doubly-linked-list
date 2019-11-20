#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

typedef union {
    intmax_t a;
    void *adr;
    long double c;
} align_data;
typedef struct node
{
    ptrdiff_t next;
    ptrdiff_t previous;
    size_t len;
    align_data data[];
} node;

int main()
{
    node *new = malloc(sizeof(node));
    align_data data[1];

    printf("%ld \n", sizeof(node));
    return 0;
}