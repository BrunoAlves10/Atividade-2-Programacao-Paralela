#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int signal_sent = 0;

void* aguardando_sinal(void* arg) {
    pthread_mutex_lock(&mutex);
    while(!signal_sent) {
        pthread_cond_wait(&cond, &mutex);
    }
    printf("Thread recebeu o sinal!\n");
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* enviando_sinal(void* arg) {
    pthread_mutex_lock(&mutex);
    signal_sent = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    printf("Sinal enviado.\n");
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, aguardando_sinal, NULL);
    pthread_create(&thread2, NULL, enviando_sinal, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}
