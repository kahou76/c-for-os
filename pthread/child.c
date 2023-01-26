#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

void* fun(void* arg) {
    char* str = (char*)arg;
    double* pd = malloc(sizeof(double));
    *pd = atof(str);
    return pd;
}

int main() {
    pthread_t tid;
    pthread_create(&tid, NULL, fun, "1.234");
    double* pd;
    pthread_join(tid, (void **) &pd);
    printf("d = %f \n", *pd);
    return 0;
}