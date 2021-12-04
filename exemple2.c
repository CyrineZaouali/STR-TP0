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

  //Exemple de 2 Tâches sous POSIX
    pthread_t task1, task2;
    pthread_create(&task1, NULL, func, (void*)1);
    pthread_create(&task2, NULL, func, (void*)2);
    pthread_join(task1, NULL);
    pthread_join(task2, NULL);

  //Forcer la non-attente d'une Tâche
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_t t3;
    pthread_create(&t3, &attr, func, (void*)3);
    pthread_attr_destroy(&attr);  
    
    return 0;
}
