#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> //para a função sqrt e pow

    typedef struct {
        int valor;
        int linha;
        int coluna;
    } Ponto;

    typedef struct {
        int linha;
        int coluna;
    } Semente;

    float distancia(int linha1, int coluna1, int linha2, int coluna2) {
        return sqrt(pow(linha2 - linha1, 2) + pow(coluna2 - coluna1, 2));
    }

    int main() {
        int linhas, colunas, qntSementes;

        printf("Insira a quantidade de linhas da matriz, considerando 0: ");
        scanf("%d", &linhas);

        printf("Insira a quantidade de colunas da matriz, considerando 0: ");
        scanf("%d", &colunas);

        printf("Insira a quantidade de sementes: ");
        scanf("%d", &qntSementes);

        Ponto **matriz;

        //alocação de memória para a matriz
        matriz = (Ponto**) malloc(linhas * sizeof(Ponto*));
        if(matriz == NULL) {
            printf("Erro ao alocar memória para linhas de matriz.");
            return 1;
        }

        //alocação de memória para elementos das linhas
        for (int i = 0; i < linhas; i++) {
            matriz[i] = (Ponto*) malloc(colunas * sizeof(Ponto));
            if(matriz[i] == NULL) {
                printf("Erro ao alocar memória para matriz");

                //liberar memória
                for(int j = 0; j < i; j++) {
                    free(matriz[j]);
                }
                free(matriz);

                return 1;
            }
        }

        //geração de sementes
        srand(time(NULL));
        Semente *sementes = (Semente*) malloc(qntSementes * sizeof(Semente));
        //teste de alocação
        if(sementes == NULL) {
            printf("Erro ao alocar memória para array de sementes.");

            //liberar memória alocada para a matriz
            for(int i = 0; i < linhas; i++) {
                free(matriz[i]);
            }
            free(matriz);

            return 1;
        }


        //atribuindo coordenadas aleatórias
        printf("Coordenadas das sementes:\n");
        for (int i = 0; i < qntSementes; i++) {
            int linha, coluna;
            int sementeRepetida;

            do {
                linha = rand() % linhas;
                coluna = rand() % colunas;
                sementeRepetida = 0;

                //verifica se a semente gerada já existe
                for (int j = 0; j < i; j++) {
                    if (linha == sementes[j].linha && coluna == sementes[j].coluna) { //compara linha e coluna aleatória com as já existentes
                        sementeRepetida = 1; //se ambas existirem, quer dizer que já tem uma semente no ponto
                        break;
                    }
                }

            } while (sementeRepetida); //repete o processo se for 1 até encontrar uma semente única

            //quando for 0, atribui as linhas e colunas aleatórias como uma nova semente
            sementes[i].linha = linha;
            sementes[i].coluna = coluna;

            printf("Semente %d: (%d, %d)\n", i+1, linha, coluna);
        }


        //preenchimento da matriz com sementes e atribuição de pontos
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                matriz[i][j].linha = i; //armazena a linha do ponto
                matriz[i][j].coluna = j; //armazena a coluna do ponto

                //verifica se o ponto atual é uma semente para evitar sobreescrita
                int ehSemente = 0;

                for (int k = 0; k < qntSementes; k++) {
                    if (i == sementes[k].linha && j == sementes[k].coluna) { //compara linha e coluna atual com vetor de sementes
                        matriz[i][j].valor = k + 1; //valor da semente é atribuido na matriz
                        ehSemente = 1;
                        break;
                    }
                }

                //se o ponto não é uma semente, atribui o valor da semente mais próxima
                if (!ehSemente) {
                    float menorDistancia = distancia(i, j, sementes[0].linha, sementes[0].coluna);
                    matriz[i][j].valor = 1; //primeira semente como a mais próxima inicialmente

                    for (int k = 1; k < qntSementes; k++) {
                        float dist = distancia(i, j, sementes[k].linha, sementes[k].coluna); //calcula próximas sementes
                        if (dist < menorDistancia) { //compara se outras sementes são menores que a semente inicial
                            menorDistancia = dist;
                            matriz[i][j].valor = k + 1; //se sim, troca o valor da semente mais próxima
                        }
                    }
                }
            }
        }

        //impressão da matriz
        printf("\nDiagrama de Voronoi:\n");
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                printf("%d ", matriz[i][j].valor);
            }
            printf("\n");
        }

        //liberação de memória 
        for (int i = 0; i < linhas; i++) {
            free(matriz[i]);
        }
        free(matriz);
        free(sementes);

        return 0;
    }
