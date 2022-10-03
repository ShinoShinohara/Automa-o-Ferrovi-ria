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

// Quando um trem chega na estação ele invocará a função station_load_train(struct station *station, int count), cujo segundo argumento indica o número de vagas disponíveis no trem.Essa função não deve encerrar sua execução até que : todos os passageiros estejam em seus assentos e todos os lugares do trem estejam ocupados ou não existam mais passageiros para embarcar.
void station_load_train(struct station *station, int count);

// Quando um passageiro chega na estação ele invocará a função station_wait_for_train(struct station *station) Essa função não deve encerrar sua execução até que : exista um trem na estação(isto é, há uma execução da função station_load_train em andamento) e existam vagas o bastante para esse passageiro sentar - se no trem.
void station_wait_for_train(struct station *station);

// Ao se acomodar em seu assento o passageiro invocará a função station_on_board(struct station *station), para notificar ao trem que já embarcou.
void station_on_board(struct station *station);

#endif