#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define NUM_REPETICIONES 10

/*
-- Enunciado:
Escriba una rutina en lenguaje C, donde se crean dos hilos calesquiera, 
estos hilos serian lanzados en paralelo. Implemente un semáforo para ambos procesos,
donde se garantice la exclusión mutua entre ambos.
*/

static void * ingresar_dinero(void* arg);
static void * extraer_dinero(void* arg);

sem_t sem;
int saldo = 100000;

int main(void){
        pthread_t hilo_1, hilo_2;

        sem_init(&sem, 0, 1);
        for(int i = 0; i < NUM_REPETICIONES; i++){
                pthread_create(&hilo_1, NULL, ingresar_dinero, NULL);
                pthread_create(&hilo_2, NULL, extraer_dinero, NULL);
        }
        pthread_join(hilo_1, NULL);
        pthread_join(hilo_2, NULL);

        return 0;
}
static void * ingresar_dinero(void* arg){
	sem_wait(&sem);
                int saldo_a_ingresar = 0;
                printf("\n---INGRESAR DINERO---");
                printf("\nMonto a ingresar: ");
                scanf("%d",&saldo_a_ingresar);

                if(saldo_a_ingresar > 0){
                        saldo = saldo + saldo_a_ingresar;
                }else{
                        printf("\nEl saldo a ingresar debe ser positivo.");
                }
                printf("\nSaldo: %d", saldo);
        sem_post(&sem);
}
static void * extraer_dinero(void* arg){
        sem_wait(&sem);
                int saldo_a_extraer = 0;
                printf("\n---EXTRAER DINERO---");
                printf("\nMonto a extraer: ");
                scanf("%d",&saldo_a_extraer);

                if(saldo >= saldo_a_extraer){
                        saldo = saldo - saldo_a_extraer;
                }else{
                        printf("\nNo cuenta con ese saldo para extraer.");
                }
                printf("\nSaldo: %d\n", saldo);
        sem_post(&sem);
}
