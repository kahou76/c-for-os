#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *ThreadFunc(void *);

int count = 0;

int main(int argc, char *argv[])
{
    pthread_attr_t attr;
    pthread_t tid;

    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, ThreadFunc, (void *)argv[1]);

    for (int i = 0; i < 10; i++)
    {
        sleep(1);
        printf("Parent: count %d\n", i);
        printf("Parent: global count %d\n", count++);
    }

    pthread_join(tid, NULL);

    return 1;
}

void *ThreadFunc(void *arg)
{
    printf("Child argument is %s\n", (char *)arg);

    for (int i = 0; i < 3; i++)
    {
        sleep(2);
        printf("Child: count %d\n", i);
        printf("child: global count %d\n", count++);
    }
}