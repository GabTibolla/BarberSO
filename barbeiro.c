// Inclusão de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

// Declaração de variáveis globais
uint n, mincorte, maxcorte, min, max, cli;
int clientesAtendidos = 0, clientesSemEsperar = 0, qntDormiu = 0, foramEmbora = 0, flag=TRUE;
sem_t barb;

// variaveis compartilhadas
int verifica = 0;

// Declaração de funções

void *barbearia(void *qualquercoisa);
void *clientes(void *qualquercoisa);
void atendimento();
void chegadaClientes();

// Programa principal
int main(int argc, char * argv[]){

    // Declaração e inicialização de variáveis
    pthread_t bar;  // Thread Barbeiro
    pthread_t clie; // Thread Clientes
    sem_init(&barb, 0, 1);

    // Testando se os parâmetros foram todos passados, caso não, mostra as condições e encerra a execução 
    if (argc != 7){
        printf("N: a quantidade de cadeiras de espera disponíveis na barbearia sendo 10 > N > 2\n");
        printf("MINCORTE: tempo mínimo gasto num atendimento do barbeiro, sendo 10 < MINCORTE < 20\n");
        printf("MAXCORTE: tempo máximo gasto num atendimento do barbeiro, sendo MINCORTE < MAXCORTE < 40\n");
        printf("MIN: tempo mínimo de intervalo entre a chegada de dois clientes sendo 1 < MIN < 5\n");
        printf("MAX: tempo máximo de intervalo entre a chegada de dois clientes sendo MIN < MAX < 15\n");
        printf("CLI: quantidade de clientes que deve chegar a barbearia sendo 1 < CLI< 100\n");
        exit(0);
    }

    // Convertendo os parâmetros para inteiros
    n = atoi(argv[1]);
    mincorte = atoi(argv[2]);
    maxcorte = atoi(argv[3]);
    min = atoi(argv[4]);
    max = atoi(argv[5]);
    cli = atoi(argv[6]);

    // Criando thread do barbeiro
    pthread_create(&bar, NULL, barbearia, NULL);

    // Criando threads dos clientes
    pthread_create(&clie, NULL, clientes, NULL);

    // Sincronizando threads clientes
    pthread_join(clie, NULL);

    // Sincronizando thread barbeiro
    pthread_join(bar, NULL);

    // Exibindo resultados ao fim do programa
    printf("Barbeiro fechou a barbearia\n");
    printf("Clientes atendidos: %d\n", clientesAtendidos);
    printf("Clientes atendidos sem esperar: %d\n", clientesSemEsperar);
    printf("Clientes que foram embora sem serem atendidos: %d\n", foramEmbora);
    printf("Quantidade de vezes que o barbeiro dormiu: %d\n", qntDormiu);

    return 0;
}

// Função para as threads, simulando a barbearia
void *barbearia(void *qualquercoisa){
    printf("Barbeiro abriu a barbearia\n");
    printf("Ninguém para atender, barbeiro foi dormir\n");

    do {
        
        
    } while (clientesAtendidos < cli);

    return NULL;
}

// Função para as threads, simulando os clientes na barbearia
void *clientes(void *qualquercoisa){
    while (clientesAtendidos < cli){
        chegadaClientes();

        sem_wait(&barb);
        verifica++;
        printf("passou  somando %dx\n", verifica);
        sem_post(&barb);

        if (verifica == 0 && clientesAtendidos != 0){
            printf("Ninguém para atender, barbeiro foi dormir\n");
            qntDormiu++;
        }

        else if (verifica == 1){
            printf("Cliente chegou e foi atendido imeadiatamente\n");
            clientesSemEsperar++;
        }

        else if (verifica > 1 && verifica <= n+1){
            printf("Cliente chegou e sentou em uma cadeira de espera\n");
        }

        else if (verifica == n+2){
            printf("Cliente foi embora sem atendimento\n");
            foramEmbora++;
        }
    }

    return NULL;
}

// Função para simular um tempo entre um atendimento e outro
void atendimento(){
    printf("Barbeiro iniciou o atendimento de um cliente\n");
    srand(time(NULL));
    //usleep(mincorte + (rand() % (maxcorte/2)));
    sleep(2);
    sem_wait(&barb);
    clientesAtendidos++;
    verifica--;
    printf("passou %dx\n", verifica);
    sem_post(&barb);
    printf("Barbeiro finalizou o atendimento de um cliente\n");
}

void chegadaClientes(){
    srand(time(NULL));
    //usleep((min + rand() % (max/2)));
    sleep(1);
}