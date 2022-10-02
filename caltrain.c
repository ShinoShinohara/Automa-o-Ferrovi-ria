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