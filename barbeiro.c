// Inclusão de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

// Declaração de variáveis globais
uint n, mincorte, maxcorte, min, max, cli;
int contador = 0, verifica = 0;
sem_t barb;
sem_t cadeiras[9];

// Declaração de funções
void *barbeiro(void *qualquercoisa);
void barbearia();
void *clientes(void *qualquercoisa);
void finaliza_atendimento();
void atendimento();
void chegadaClientes();

// Programa principal
int main(int argc, char * argv[]){

    // Declaração e inicialização de variáveis
    int i;
    pthread_t bar;
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

    // Declarando a variável clientes conforme escolhida pelo usuário
    pthread_t clie[cli];

    // Iniciando semaforo das cadeiras
    for (i = 0; i < n; i++){
        sem_init(&cadeiras[i], 0, 1);
    }

    // Criando thread do barbeiro
    pthread_create(&bar, NULL, barbeiro, NULL);

    // Criando threads dos clientes
    for (i = 0; i < cli; i++){
        chegadaClientes();
        pthread_create(&clie[i], NULL, clientes, NULL);
    }

    // Sincronizando threads clientes
    for (i = 0; i < cli; i++){
        pthread_join(clie[i], NULL);
    }
    // Sincronizando thread barbeiro
    pthread_join(bar, NULL);

    return 0;
}

// Função para thread barbeiro
void *barbeiro(void *qualquercoisa){
    printf("Barbeiro abriu a barbearia\n");
    printf("Ninguém para atender, barbeiro foi dormir\n");
}

// Função para as threads clientes
void *clientes(void *qualquercoisa){
    verifica++;
    barbearia();
}

void barbearia(){

}

void finaliza_atendimento(){

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