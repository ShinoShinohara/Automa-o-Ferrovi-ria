#ifndef STATION_H
#define STATION_H

#include <pthread.h>
#include <stdbool.h>

struct station
{
    int assentos_disponiveis;
    int passageiros_esperando;
    int passageiros_entraram;
    pthread_mutex_t mutex;
};

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);

#endif