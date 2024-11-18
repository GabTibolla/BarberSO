Implementação concorrente do Barbeiro Dorminhoco
O problema do barbeiro adormecido pode ser descrito da seguinte forma: uma barbearia contém um
(1) barbeiro, uma (1) cadeira para atendimento e N cadeiras de espera (N > 1). O barbeiro chega e abre a
barbearia. Sempre que não existirem clientes o barbeiro dorme na cadeira de atendimento. Quando um
cliente chega, acorda o barbeiro e este procede a realização do serviço (corte de barba ou cabelo).
Enquanto o barbeiro está
ocupado atendendo um cliente,
novos clientes podem chegar a
barbearia. Se o barbeiro está
ocupado, ao chegar um novo
cliente este senta em uma cadeira
de espera ou vai embora, caso não
existam cadeiras de espera
disponíveis. Ao terminar um
atendimento, o babeiro chama o
próximo cliente e caso não
existem clientes esperando volta a
dormir.
O problema consiste em
programar o problema do barbeiro
adormecido e fazê-lo funcionar de
forma concorrente. Deve ser
implementado em C/C++, sendo o
barbeiro implementado por meio
de uma thread e outra thread deve
ser usada para simular a chegada de clientes a barbearia. O atendimento pode ser simulado por meio da
função usleep(), sendo gerado um valor aleatório entre MINCORTE e MAXCORTE, representando o
tempo em minutos que demora para um barbeiro realizar um atendimento. A chegada de um cliente deve
ser aleatória, sendo que um novo deve chegar após um valor entre MIN e MAX representando o tempo
em minutos entre a chegada de clientes. Deve-se informar ainda a quantidade de clientes que chegam a
barbearia (CLI), antes de encerrar a execução.

Entrada:
A entrada no programa deve ser realizada por meio da linha de comando. Elá é composta por seis
inteiros positivos N, MINCORTE, MAXCORTE, MIN, MAX e CLI. Caso não sejam informados a
quantidade correta de argumentos o programa não deve ser executado.
 Um inteiro N que informa a quantidade de cadeiras de espera disponíveis na barbearia sendo
10 > N > 2;
 Um inteiro MINCORTE representando o tempo mínimo gasto num atendimento do barbeiro,
sendo 10 < MINCORTE < 20;
 Um inteiro MAXCORTE representando o tempo máximo gasto num atendimento do barbeiro,
sendo MINCORTE < MAXCORTE < 40;
 Um inteiro MIN representando o tempo mínimo de intervalo entre a chegada de dois clientes
sendo 1 < MIN < 5;
 Um inteiro MAX representando o tempo máximo de intervalo entre a chegada de dois clientes
sendo MIN < MAX < 15;
 Um inteiro CLI indicando a quantidade de clientes que deve chegar a barbearia sendo
1 < CLI< 100.

Saída:
A saída deve ser mostrada na saída padrão. Deve-se mostrar a atividade do barbeiro e a chegada dos
clientes.

Mostrar as seguintes ações do barbeiro:
 Abriu a barbearia;
 Quando foi dormir (não há clientes para atender);
 Quando iniciou o atendimento de um cliente;
 Quando finalizou o atendimento de um cliente;
 Fechou a barbearia;

Mostrar as seguintes ações de cada clientes:
 Chegou e foi atendido imediatamente;
 Chegou e foi sentar numa das cadeiras de espera;
 Chegou e foi embora pois não foi atendido e não podia sentar (não há cadeiras disponíveis);

Ao final do programa, deve ser mostrado:
 Quantidade de clientes que foram atendidos;
 Quantidade de clientes que foram atendidos sem esperar nas cadeiras de espera;
 Quantidade de clientes que chegaram a barbearia e foram embora, sem serem atendidos;
 Quantas vezes o barbeiro foi dormir enquanto a barbearia estava aberta;


Exemplo de execução:
./barbeiro 3 15 35 5 10 10
Barbeiro abriu a barbearia
Ninguém para atender, barbeiro foi dormir
Cliente chegou e será atendido sem esperar
Barbeiro iniciando o atendimento de um cliente
Cliente chegou e foi sentar em cadeira de espera
Barbeiro finalizou o atendimento de um cliente
Barbeiro iniciando o atendimento de um cliente
Cliente chegou e foi sentar em cadeira de espera
Cliente chegou e foi sentar em cadeira de espera
Barbeiro finalizou o atendimento de um cliente
Barbeiro iniciando o atendimento de um cliente
Cliente chegou e foi sentar em cadeira de espera
Barbeiro finalizou o atendimento de um cliente
Barbeiro iniciando o atendimento de um cliente
Cliente chegou e foi sentar em cadeira de espera
Cliente chegou e foi sentar em cadeira de espera
Barbeiro finalizou o atendimento de um cliente
Barbeiro iniciando o atendimento de um cliente
Cliente chegou e foi sentar em cadeira de espera
Barbeiro finalizou o atendimento de um cliente
Barbeiro iniciando o atendimento de um cliente
Cliente chegou e foi sentar em cadeira de espera
Barbeiro finalizou o atendimento de um cliente
Barbeiro iniciando o atendimento de um cliente
Cliente chegou e foi sentar em cadeira de espera
Barbeiro finalizou o atendimento de um cliente
Barbeiro iniciando o atendimento de um cliente
Barbeiro finalizou o atendimento de um cliente
Barbeiro iniciando o atendimento de um cliente
Barbeiro finalizou o atendimento de um cliente
Barbeiro iniciando o atendimento de um cliente
Barbeiro finalizou o atendimento de um cliente
Barbeiro fechou a barbearia
Clientes atendidos: 10
Clientes atendidos sem esperar: 1
Clientes que foram embora, sem serem atendidos: 0
Quantidade de vezes que o barbeiro dormiu: 1


Exemplo de execução:
./barbeiro 3 15 35 50 100 10
Barbeiro abriu a barbearia
Ninguém para atender, barbeiro foi dormir
Cliente chegou e será atendido sem esperar
Barbeiro iniciando o atendimento de um cliente
Cliente chegou e foi sentar em cadeira de espera
Barbeiro finalizou o atendimento de um cliente
Barbeiro iniciando o atendimento de um cliente
Cliente chegou e foi sentar em cadeira de espera
Barbeiro finalizou o atendimento de um cliente
Barbeiro iniciando o atendimento de um cliente
Barbeiro finalizou o atendimento de um cliente
Ninguém para atender, barbeiro foi dormir
Cliente chegou e será atendido sem esperar
Barbeiro iniciando o atendimento de um cliente
Barbeiro finalizou o atendimento de um cliente
Ninguém para atender, barbeiro foi dormir
Cliente chegou e será atendido sem esperar
Barbeiro iniciando o atendimento de um cliente
Barbeiro finalizou o atendimento de um cliente
Cliente chegou e será atendido sem esperar
Ninguém para atender, barbeiro foi dormir
Barbeiro iniciando o atendimento de um cliente
Barbeiro finalizou o atendimento de um cliente
Ninguém para atender, barbeiro foi dormir
Cliente chegou e será atendido sem esperar
Barbeiro iniciando o atendimento de um cliente
Cliente chegou e foi sentar em cadeira de espera
Barbeiro finalizou o atendimento de um cliente
Barbeiro iniciando o atendimento de um cliente
Cliente chegou e foi sentar em cadeira de espera
Barbeiro finalizou o atendimento de um cliente
Barbeiro iniciando o atendimento de um cliente
Barbeiro finalizou o atendimento de um cliente
Ninguém para atender, barbeiro foi dormir
Cliente chegou e será atendido sem esperar
Barbeiro iniciando o atendimento de um cliente
Barbeiro finalizou o atendimento de um cliente
Barbeiro fechou a barbearia
Clientes atendidos: 10
Clientes atendidos sem esperar: 6
Clientes que foram embora, sem serem atendidos: 0
Quantidade de vezes que o barbeiro dormiu: 6
