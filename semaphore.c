#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <unistd.h>
#include<semaphore.h>

sem_t event;

void* task1(void* arg) {
    int i = 0;
    while(i<10) {
        printf("La tache %s d'execute\n", (char*)arg);
        sem_post(&event);
        i++;
    }
}

void* task2(void* arg) {
    int i = 0;
    while(i<10) {
        sem_wait(&event);
        printf("La tache %s d'execute enfin\n", (char*)arg);
        i++;
    }
}

int main(){
    pthread_t thread1, thread2;
    sem_init(&event,0,0);
    pthread_create(&thread1,NULL,task1,"1");
    pthread_join(thread1,NULL);
    pthread_create(&thread2,NULL,task2,"2");
    pthread_join(thread2,NULL);
    return 0;
}