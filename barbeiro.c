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
int contador = 0, verifica = 0, status[9], flag = FALSE, conta = 0;
sem_t barb;

// Declaração de funções
void *barbeiro(void *qualquercoisa);
void barbearia_barb();
void barbearia_clien();
void *clientes(void *qualquercoisa);
void finaliza_atendimento();
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
    pthread_create(&bar, NULL, barbeiro, NULL);

    // Criando threads dos clientes
    pthread_create(&clie, NULL, clientes, NULL);

    // Sincronizando threads clientes
    pthread_join(clie, NULL);

    // Sincronizando thread barbeiro
    pthread_join(bar, NULL);

    return 0;
}

// Função para thread barbeiro
void *barbeiro(void *qualquercoisa){
    printf("Barbeiro abriu a barbearia\n");
    printf("Ninguém para atender, barbeiro foi dormir\n");
    barbearia_barb();

    return NULL;
}

// Função para as threads clientes
void *clientes(void *qualquercoisa){
    barbearia_clien();
    return NULL;
}

// Função para simular o funcionamento da barbearia na visão do barbeiro
void barbearia_barb(){
    while (contador <= cli){
        if (verifica == 0 && contador != 0 && flag){
            printf("Ninguém para atender, barbeiro foi dormir\n");
            sem_wait(&barb);
            printf("Barbeiro iniciou o atendimento de um cliente\n");
            flag = FALSE;
            atendimento();
            finaliza_atendimento();
        }
        else if (verifica == 1 && flag){
            printf("Cliente chegou e foi atendido imediatamente\n");
            sem_wait(&barb);
            printf("Barbeiro iniciou o atendimento de um cliente\n");
            flag = FALSE;
            atendimento();
            finaliza_atendimento();
        }
        else if (verifica > 1 && flag){
            printf("Barbeiro iniciou o atendimento de um cliente\n");
            sem_wait(&barb);
            flag = FALSE;
            atendimento();
            finaliza_atendimento();
        }
    }
}

// Função para simular o funcionamento da barbearia na visão do cliente
void barbearia_clien(){
    while (conta < cli){
        chegadaClientes();
        verifica++;
        if (verifica == n){
            printf("Cliente chegou e foi embora sem atendimento\n");
        }
        else if (verifica < n){
            printf("Cliente chegou e sentou em uma cadeira de espera\n");
            flag = TRUE;
        }
    }
}

// Função para finalizar atendimento e restaurar algumas variáveis
void finaliza_atendimento(){
    printf("Barbeiro finalizou um atendimento\n");
    verifica--;
    conta++;
    contador++;
    sem_post(&barb);
}

// Função para simular um tempo entre um atendimento e outro
void atendimento(){
    srand(time(NULL));
    usleep(mincorte + (rand() % (maxcorte/2)));
}

// Função para simular um tempo entre a chegada de um cliente e outro
void chegadaClientes(){
    srand(time(NULL));
    usleep((min + rand() % (max/2)));
}