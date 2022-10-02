# Automação-Ferroviaria
Trabalho de SO - Tema n° 5

5) Automação Ferroviária

Uma companhia ferroviária decidiu melhorar o desempenho de suas estações, e para isso decidiu robotizar tanto os seus trens, quanto os seus passageiros! Cada trem será controlado por uma thread, assim como cada passageiro. Você foi contratado para implementar essa automação.

Você deverá definir uma struct station e as funções descritas a seguir.

Quando um trem chega na estação ele invocará a função station_load_train(struct station *station, int count), cujo segundo argumento indica o número de vagas disponíveis no trem.  Essa função não deve encerrar sua execução até que: todos os passageiros estejam em seus assentos; e todos os lugares do trem estejam ocupados ou não existam mais passageiros para embarcar.

Quando um passageiro chega na estação ele invocará a função station_wait_for_train(struct station *station) Essa função não deve encerrar sua execução até que: exista um trem na estação (isto é, há uma execução da função station_load_train em andamento); e existam vagas o bastante para esse passageiro sentar-se no trem.

Ao se acomodar em seu assento o passageiro invocará a função station_on_board(struct station *station), para notificar ao trem que já embarcou.

Codifique em um arquivo caltrain.c a especificação da struct station, definindo as funções descritas acima, além da função station_init que será invocada para a configuração inicial da estação quando a rotina for executada. 

Além disso:

utilize apenas locks/travas e conditions/condições (sem semáforos ou outras estratégias de sincronização);

não pode ser usada mais de uma trava/lock em cada struct station;

você pode assumir que nunca há mais de um trem por vez na estação, e que todos os trens e passageiros tem o mesmo destino (isto é, qualquer passageiro pode 
embarcar em qualquer trem);

seu código deve permitir que múltiplos passageiros embarquem simultaneamente (deve ser possível que vários passageiros simultaneamente invoquem a função station_wait_for_train, e até mesmo que a função já tenha encerrado sua execução para cada um desses passageiros, antes que qualquer um deles tenha invocado a função station_on_board);

seu código não deve causar busy-waiting, isto é, não deve utilizar-se de loops para esperar indefinidamente por condições
