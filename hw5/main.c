#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int sum = 0;
pthread_mutex_t mtx;

struct args
{
    int *a;
    int start;
    int end;
};

void *work(void *arg)
{
    struct args *p = (struct args *)arg;
    int s = 0;
    for (int i = p->start; i < p->end; i++)
    {
        s += p->a[i];
    }

    pthread_mutex_lock(&mtx);
    sum += s;
    pthread_mutex_unlock(&mtx);

    return NULL;
}

int main()
{
    int n;
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
        printf("%d ", a[i]);
    }
    printf("\n");

    pthread_t t[4];
    struct args p[4];
    pthread_mutex_init(&mtx, NULL);

    int size = n / 4;
    for (int i = 0; i < 4; i++)
    {
        p[i].a = a;
        p[i].start = i * size;
        if (i == 3)
        {
            p[i].end = n;
        }
        else
        {
            p[i].end = (i + 1) * size;
        }
        pthread_create(&t[i], NULL, work, &p[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        pthread_join(t[i], NULL);
    }

    printf("Sum = %d\n", sum);

    pthread_mutex_destroy(&mtx);
    free(a);

    return 0;
}