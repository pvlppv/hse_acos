#include <stdio.h>
#include <stdlib.h>

struct node {
    int x;
    struct node *n;
};

int main() {
    struct node *h = NULL, *a, *b;
    int z;
    while (1) {
        scanf("%d", &z);
        if (z == 0) break;
        a = (struct node*)malloc(sizeof(struct node));
        a->x = z;
        a->n = NULL;
        if (h == NULL) h = a;
        else {
            b = h;
            while (b->n != NULL) b = b->n;
            b->n = a;
        }
    }
    a = NULL;
    b = h;
    while (b != NULL) {
        struct node *c = b->n;
        b->n = a;
        a = b;
        b = c;
    }
    h = a;
    while (h != NULL) {
        printf("%d ", h->x);
        b = h;
        h = h->n;
        free(b);
    }
    return 0;
}