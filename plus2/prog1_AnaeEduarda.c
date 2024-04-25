#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

    typedef struct {
        int valor;
    } Ponto;

    typedef struct {
        int linha;
        int coluna;
    } Semente;

    float distancia(int i, int j, int linha, int coluna) {
        return sqrt(pow(linha - i, 2) + pow(coluna - j, 2));
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

        for (int i = 0; i < linhas; i++) {
            matriz[i] = (Ponto*) malloc(colunas * sizeof(Ponto));
            if(matriz[i] == NULL) {
                printf("Erro ao alocar memória para matriz");

                // Liberar memória alocada
                for(int j = 0; j < i; j++) {
                    free(matriz[j]);
                }
                free(matriz);

                return 1;
            }
        }

        //alocação de memória para o array de sementes
        Semente *sementes = (Semente*) malloc(qntSementes * sizeof(Semente));
        if(sementes == NULL) {
            printf("Erro ao alocar memória para array de sementes.");

            //liberar memória alocada para a matriz
            for(int i = 0; i < linhas; i++) {
                free(matriz[i]);
            }
            free(matriz);

            return 1;
        }

        //geração de sementes com coordenadas aleatórias
        srand(time(NULL));
        for (int i = 0; i < qntSementes; i++) {
            int linha, coluna;
            int sementeRepetida;

            do {
                linha = rand() % linhas;
                coluna = rand() % colunas;
                sementeRepetida = 0;

                //verifica se a semente gerada já existe
                for (int j = 0; j < i; j++) {
                    if (linha == sementes[j].linha && coluna == sementes[j].coluna) {
                        sementeRepetida = 1;
                        break;
                    }
                }

            } while (sementeRepetida); //repete o processo até encontrar uma semente única

            sementes[i].linha = linha;
            sementes[i].coluna = coluna;

            printf("Semente %d: (%d, %d)\n", i+1, linha, coluna);
        }

        //preenchimento da matriz com sementes e pontos
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                int ehSemente = 0;

                for (int k = 0; k < qntSementes; k++) { //verifica se é semente
                    if (i == sementes[k].linha && j == sementes[k].coluna) {
                        matriz[i][j].valor = k + 1; //salva valor da semente
                        ehSemente = 1;
                        break;
                    }
                }

                if (!ehSemente) { //se não for semente, salva como 0
                    matriz[i][j].valor = 0; //ponto
                }
            }
        }

        //impressão da matriz
        printf("\nDiagrama de Voronoi:\n");
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                if (matriz[i][j].valor == 0) {
                    printf("."); //se não for semente, rpinta 0
                } else {
                    printf("%d", matriz[i][j].valor);
                }
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
