#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    float size;
    float weight;
} type_shared_data;

pthread_mutex_t lock;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
type_shared_data shared_data;

void* task1(void* arg) {
    type_shared_data my_shared_data;
    int i = 0;
    while(i<10) {
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&cond,&lock);
        my_shared_data = shared_data;
        pthread_mutex_unlock(&lock);
        printf("La tache %s vient de lire la donnée partagée\n", (char*) arg); 
        usleep(1000000); 
        i++;
    }
}

void* task2(void* arg) {
    type_shared_data my_shared_data;
    int i = 0;
    while(i<10) {
        pthread_mutex_lock(&lock);
        shared_data.size = 100 + rand()%101;
        shared_data.weight = 10 + rand()%101;
        if(shared_data.size >= 120 && shared_data.weight >= 60) {
            pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&lock);
        printf("La tache %s vient de modifier la donnée partagée\n", (char*) arg); 
        usleep(1000000); 
        i++;
    }
}

int main(void) {
    pthread_t thread1, thread2;
    pthread_mutex_init(&lock, NULL);
    shared_data.size = 100 + rand()%101;
    shared_data.weight = 10 + rand()%101;
    pthread_create(&thread1, NULL, task1, "1");
    pthread_create(&thread2, NULL, task2, "2");
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}
