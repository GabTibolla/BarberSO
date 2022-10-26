/*
@Barbeiro Adormecido

- Juan Pinto Loureiro
- Gabriel Matheus Tibolla

link git: https://github.com/GabTibolla/BarberSO
*/


// Inclusão de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>

// Declaração de constantes usadas pela variável FLAG
#define TRUE 1
#define FALSE 0

// Declaração de variáveis globais
uint n, mincorte, maxcorte, min, max, cli;
int clientesAtendidos = 0, clientesSemEsperar = 0, qntDormiu = 0, foramEmbora = 0, flag = TRUE, contador = 0;
sem_t barb;

// variaveis compartilhadas
uint verifica = 0;

// Declaração de funções

void *barbeiro(void *qualquercoisa);
void *clientes(void *qualquercoisa);
void atendimento();
void chegadaClientes();

// Programa principal
int main(int argc, char *argv[])
{

    // Declaração e inicialização de variáveis
    pthread_t bar;  // Thread Barbeiro
    pthread_t clie; // Thread Clientes
    sem_init(&barb, 0, 1);  // Inicializando o semáforo

    // Testando se os parâmetros foram todos passados, caso não, mostra as condições e encerra a execução
    if (argc != 7)
    {
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

    // Exibindo resultados ao fim do programa
    printf("Barbeiro fechou a barbearia\n");
    printf("Clientes atendidos: %d\n", clientesAtendidos);
    printf("Clientes atendidos sem esperar: %d\n", clientesSemEsperar);
    printf("Clientes que foram embora sem serem atendidos: %d\n", foramEmbora);
    printf("Quantidade de vezes que o barbeiro dormiu: %d\n", qntDormiu);

    return 0;
}

// Função para as threads, simulando a função do barbeiro: enquanto houver clientes, realizar o atendimento
void *barbeiro(void *qualquercoisa)
{
    printf("Barbeiro abriu a barbearia\n");
    printf("Ninguém para atender, barbeiro foi dormir\n");  // Sempre que o barbeiro abre a barbearia, nunca haverá clientes, ou seja, ele irá dormir
    flag = FALSE;

    while ((verifica > 0) || (clientesAtendidos < cli))
    {
        if (verifica > 0 && flag)  // Enquanto houver clientes, continuar atendendo
            atendimento();

        else if (clientesAtendidos == cli)  // Caso o número de clientes atendidos seja satisfeito, encerra o laço while
            break;
    }

    return NULL;
}

// Função para as threads, simulando os clientes na barbearia
void *clientes(void *qualquercoisa)
{
    while (contador < cli)   // Esta verificação com um contador é para não chegar um número de clientes maior do que passado em CLI
    {
        chegadaClientes();

        // If para verificar se o barbeiro pode dormir, não será executado logo na primeira execução para não repetir o print
        if (verifica == 0 && clientesAtendidos != 0)
        {
            printf("Ninguém para atender, barbeiro foi dormir\n");
            qntDormiu++;
        }

        // If para verificar o primeiro atendimento, no caso, o atendimento imediato
        else if (verifica == 1)
        {
            flag = TRUE;
            printf("Cliente chegou e foi atendido imeadiatamente\n");
            clientesSemEsperar++;
        }
        
        // Verifica se ainda há cadeiras disponíveis
        else if (verifica > 1 && verifica <= n + 1)
        {
            printf("Cliente chegou e sentou em uma cadeira de espera\n");
        }

        // Caso o número de clientes seja o mesmo número de clientes na barbearia (um em atendimento e mais n), cliente irá embora
        else if (verifica == n + 2)
        {
            printf("Cliente foi embora sem atendimento\n");
            foramEmbora++;
        }

        // Incrementa variável "verifica" após tempo definido pela função chegadaClientes()
        sem_wait(&barb);
        verifica++;
        contador++;
        sem_post(&barb);
    }

    return NULL;
}

// Função para simular um tempo entre um atendimento e outro
void atendimento()
{

    // Inicio da zona crítica
    sem_wait(&barb);
    if (flag)
        printf("Barbeiro iniciou o atendimento de um cliente\n");
    sem_post(&barb);
    // Fim da zona crítica

    /*
    Esse intervalo é realizado fora da zona crítica por ser em um intervalo de tempo,
    o que possibilita a chegada de novos clientes, incrementando a variável "verifica",
    que neste caso, é uma variável compartilhada
    */

    srand(time(NULL));
    usleep(mincorte + (rand() % (maxcorte / 2)));

    // Inicio da zona crítica
    sem_wait(&barb);
    printf("Barbeiro finalizou o atendimento de um cliente\n");
    verifica--;          // Diminui o número de clientes na barbearia
    clientesAtendidos++; // Incrementa variável dos clientes atendidos
    sem_post(&barb);
    // Fim da zona crítica
}

// Função para emular a chegada entre um cliente e outro
void chegadaClientes()
{
    srand(time(NULL));
    usleep((min + rand() % (max / 2)));
}