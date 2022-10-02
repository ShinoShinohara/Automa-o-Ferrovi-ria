#include <pthread.h>
#include "station.h"

void station_init(struct station *station)
{
    station->assentos_disponiveis = 0;
    station->passageiros_esperando = 0;
    station->passageiros_entraram = 0;

    pthread_mutex_init(&(station->mutex), NULL);
}