#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, t;
    int a[100];
    scanf("%d", &n);
    for (i = 0; i < n; i++) scanf("%d", &a[i]);
    for (i = 0; i < n/2; i++) {
        t = a[i];
        a[i] = a[n-1-i];
        a[n-1-i] = t;
    }
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    return 0;
}