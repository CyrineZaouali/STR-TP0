#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> 

void* func(void* arg) {
    int i;
    for(i=0; i<7; i++) {
        printf("Tache %d : %d\n", arg, i);
        usleep(1000000); //wait one second
    }
}

int main(void) {
    pthread_t task1, task2;
    pthread_attr_t attr;
    struct sched_param param;
    pthread_attr_init(&attr);

    param.sched_priority = 12;
    pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

    param.sched_priority = 10;
    pthread_attr_setschedparam(&attr, &param);
    pthread_create(&task1, &attr, func, (void*)1);

    param.sched_priority = 7;
    pthread_attr_setschedparam(&attr, &param);
    pthread_create(&task2, &attr, func, (void*)2);

    pthread_attr_destroy(&attr);
    pthread_join(task1, NULL);
    pthread_join(task2, NULL);

    return 0;
}