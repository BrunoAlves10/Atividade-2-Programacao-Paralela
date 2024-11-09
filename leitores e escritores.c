#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_rwlock_t rwlock;
int shared_data = 0;

void* leitor(void* arg) {
    pthread_rwlock_rdlock(&rwlock);
    printf("Leitor leu o valor: %d\n", shared_data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void* escritor(void* arg) {
    pthread_rwlock_wrlock(&rwlock);
    shared_data++;
    printf("Escritor atualizou o valor para: %d\n", shared_data);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

int main() {
    pthread_t leitores[5], escritores[2];
    pthread_rwlock_init(&rwlock, NULL);

    for(int i = 0; i < 5; i++) pthread_create(&leitores[i], NULL, leitor, NULL);
    for(int i = 0; i < 2; i++) pthread_create(&escritores[i], NULL, escritor, NULL);

    for(int i = 0; i < 5; i++) pthread_join(leitores[i], NULL);
    for(int i = 0; i < 2; i++) pthread_join(escritores[i], NULL);

    pthread_rwlock_destroy(&rwlock);
    return 0;
}
