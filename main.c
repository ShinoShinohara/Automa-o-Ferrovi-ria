#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>

#include "station.h"

pthread_barrier_t bar;

void *
passageiro(void *arg)
{
    struct station *station = (struct station *)arg;
    int pid = pthread_self();
    printf("Passageiro %d chegou a estação.\n", pid);
    station_wait_for_train(station);
    return NULL;
}

int main(int argc, char **argv)
{
    printf("Abrindo Estação.\n");

    struct station station;
    station_init(&station);

    station_load_train(&station, 5);

    int passageiros_total = 20;
    int passageiros_estacao = passageiros_total;
    for (int i = 0; i < passageiros_total; i++)
    {
        pthread_t tid;
        int codigo_de_erro = pthread_create(&tid, NULL, passageiro, &station);
        if (codigo_de_erro != 0)
        {
            printf("Error on thread creation= %d\n", codigo_de_erro);

            exit(1);
        }
    }

    station_load_train(&station, 5);
    station_load_train(&station, 0);
    station_load_train(&station, 4);
    station_load_train(&station, 6);
    station_load_train(&station, 10);

    pthread_barrier_wait(&bar);

    printf("Fechando Estação.\n");

    pthread_exit(NULL);
}