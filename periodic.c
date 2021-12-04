#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void* periodic_task(void* period){
    pthread_cond_t cond;
    pthread_mutex_t lock;
    struct timespec time;
    pthread_cond_init (&cond, NULL);
    pthread_mutex_init (&lock, NULL);
    int i=0;
    clock_gettime(CLOCK_REALTIME, &time);
    while(i<10){
        pthread_mutex_lock(&lock);
        time.tv_sec = time.tv_sec + (int)period;
        printf("La tache %s s'execute periodiquement à l'instant %d secondes\n", "t1", (int) time.tv_sec);
        pthread_cond_timedwait(&cond, &lock, &time);
        pthread_mutex_unlock(&lock);
        i++;
    }
}

int main(void) {
    pthread_t task;
    pthread_create(&task, NULL, periodic_task, (void*)5);
    pthread_join(task, NULL);
    return 0;
}