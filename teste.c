#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char magicNumber[3];
    int width, height;
    int maxGray;
    int **matrizP2;
} imagemP2;

typedef struct
{
    char magicNumber[3];
    int width, height;
    int maxGray;
    int **matrizP8;
} imagemP8;



void escreverArquivoP8(int** matrizP8, int* sizeLines, int altura) {
    FILE* file = fopen("C:/Users/Vitor M/Documents/GitHub/trabalho1esdd/matrizP8.txt", "w");
    char arroba = '@';

    if (file == NULL) {
        return;
    }


    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < sizeLines[i]; j++) {
            if (matrizP8[i][j] == -10) {
                fprintf(file, "%c ", arroba);
            } else {
                fprintf(file, "%d ", matrizP8[i][j]);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void compactar(int **matrizP2, int **matrizP8, int altura, int largura)
{
    matrizP8 = calloc(sizeof(int *), altura);
    int atual = matrizP2[0][0];
    int contador = 1;
    int k = 0;
    int arrayAuxiliar[24];
    int *sizeLines;

    sizeLines = (int*)calloc(sizeof(int), altura);

    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            if (j + 1 < largura && matrizP2[i][j + 1] == atual)
            {
                contador++;
            }
            else
            {
                if (contador > 3)
                {
                    arrayAuxiliar[k] = -10;
                    k++;
                    arrayAuxiliar[k] = matrizP2[i][j];
                    k++;
                    arrayAuxiliar[k] = contador;
                    k++;
                }
                else
                {
                    for (int l = 0; l < contador; l++)
                    {
                        arrayAuxiliar[k] = matrizP2[i][j];
                        k++;
                    }
                }
                if (j + 1 < largura)
                {
                    atual = matrizP2[i][j + 1];
                }
                contador = 1;
            }
            if (j + 1 == largura)
            {
                matrizP8[i] = (int *)calloc(sizeof(int), k);
                sizeLines[i] = k;
                for (int m = 0; m < k; m++)
                {
                    matrizP8[i][m] = arrayAuxiliar[m];
                }
                k = 0;
            }
        }
    }
    escreverArquivoP8(matrizP8, sizeLines, altura);
}

void descompactar(int** matrizP2, int** matrizP8, int altura, int largura){
        
}
int main()
{
    int **matrizP2;
    int **matrizP8;
    int linhas = 7, colunas = 24;

    matrizP2 = (int **)calloc(sizeof(int *), linhas);
    matrizP8 = (int **)calloc(sizeof(int *), linhas);

    for (int i = 0; i < linhas; i++)
    {
        matrizP2[i] = (int *)calloc(sizeof(int), colunas);
    }

    int matrizTesteP2[7][24] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 3, 3, 3, 3, 0, 0, 7, 7, 7, 7, 0, 0, 11, 11, 11, 11, 0, 0, 15, 15, 15, 15, 0},
        {0, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 15, 0, 0, 15, 0},
        {0, 3, 3, 3, 0, 0, 0, 7, 7, 7, 0, 0, 0, 11, 11, 11, 0, 0, 0, 15, 15, 15, 15, 0},
        {0, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0},
        {0, 3, 0, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 11, 11, 11, 11, 0, 0, 15, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    for (int i = 0; i < linhas; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            matrizP2[i][j] = matrizTesteP2[i][j];
        }
    }

    // Não se esqueça de liberar a memória alocada para a matrizP2 quando terminar de usá-la
    compactar(matrizP2, matrizP8, linhas, colunas);
    return 0;
}