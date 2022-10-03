#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include "station.h"

void station_init(struct station *station)
{
    station->assentos_disponiveis = 0;
    station->passageiros_esperando = 0;
    station->passageiros_entraram = 0;

    pthread_mutex_init(&(station->mutex), NULL);

    // p/ saber se os passageiros estao em seus assentos && todos os lugares do trem estejam ocupados ou não existam mais passageiros para embarcar
    pthread_cond_init(&(station->assentos_disponiveis), NULL);
    pthread_cond_init(&(station->passageiros_entraram), NULL);
}

void station_load_train(struct station *station, int count)
{
    pthread_mutex_lock(&(station->mutex));
    if (!count || !station->passageiros_esperando) // saber se tem gente na estação ou assentos disponiveis
    {
        pthread_mutex_unlock(&(station->mutex));
        if (!count)
            printf("Trem lotado\n");
        else if (!station->passageiros_esperando)
            printf("Estação vazia\n");
        return;
    }
    station->assentos_disponiveis = count;
    printf("Avisar os passageiros que o trem chegou.\n");
    pthread_cond_broadcast(&(station->assentos_disponiveis));
    printf("Esperando por %d passageiros entrarem.\n", count);
    pthread_cond_wait(&(station->passageiros_entraram), &(station->mutex));
    station->assentos_disponiveis = 0;
    printf("%d Passageiros entraram, preparando para sair.\n", count);
    pthread_mutex_unlock(&(station->mutex));
}

void station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&(station->mutex));
    station->passageiros_esperando++;
    while (!station->assentos_disponiveis)
        pthread_cond_wait(&(station->assentos_disponiveis), &(station->mutex));
    station->passageiros_esperando--;
    station->passageiros_entraram++;
    station->assentos_disponiveis--;
    pthread_mutex_unlock(&(station->mutex));
}

void station_on_board(struct station *station)
{
    pthread_mutex_lock(&(station->mutex)); // enter critical section
    station->passageiros_entraram;
    if (!station->passageiros_entraram && !(station->passageiros_esperando && station->assentos_disponiveis)) // all leaving passengers are on board, and no other passengers can get on the train
        pthread_cond_signal(&(station->passageiros_entraram));
    pthread_mutex_unlock(&(station->mutex)); // leave critical section
}