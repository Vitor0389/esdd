#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void alocarMatrizP2(imagemP2 *imagemPGM)
{
    imagemPGM->matrizP2 = (int **)calloc(sizeof(int *), (imagemPGM->height));

    for (int i = 0; i < imagemPGM->height; i++)
    {
        imagemPGM->matrizP2[i] = (int *)calloc(sizeof(int), (imagemPGM->width));
    }
}

void lerArquivoP2(FILE* P2, imagemP2 *imagemPGM)
{
    if (P2 == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fscanf(P2, "%s", &imagemPGM->magicNumber);
    fscanf(P2, "%d %d", &imagemPGM->width, &imagemPGM->height);
    fscanf(P2, "%d", &imagemPGM->maxGray);

    alocarMatrizP2(imagemPGM);


    for (int i = 0; i < imagemPGM->height; i++)
    {
        for (int j = 0; j < imagemPGM->width; j++)
        {
            fscanf(P2, "%d", &imagemPGM->matrizP2[i][j]);
        }
        printf("\n");
    }

    fclose(P2);
}

void AlocaMatrizP8(imagemP8 *imagemPGMC, int linhas)
{
    imagemPGMC->matrizP8 = (int**)calloc(sizeof(int *), linhas);
}
void escreverArquivoP8(imagemP8 *imagemPGMC, int *sizeLines, int altura)
{
    FILE *file = fopen("C:/Users/Vitor M/Documents/GitHub/trabalho1esdd/matrizP8.txt", "w");
    char arroba = '@';

    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < sizeLines[i]; j++)
        {
            if (imagemPGMC->matrizP8[i][j] == -10)
            {
                fprintf(file, "%c ", arroba);
            }
            else
            {
                fprintf(file, "%d ", imagemPGMC->matrizP8[i][j]);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
void compactar(imagemP2 *imagemPGM, imagemP8 *imagemPGMC)
{
    AlocaMatrizP8(imagemPGMC, imagemPGM->height);
    int atual = imagemPGM->matrizP2[0][0];
    int contador = 1;
    int k = 0;
    int arrayAuxiliar[24];
    int *sizeLines;

    sizeLines = (int *)calloc(sizeof(int), imagemPGM->height);

    for (int i = 0; i < imagemPGM->height; i++)
    {
        for (int j = 0; j < imagemPGM->width; j++)
        {
            if (j + 1 < imagemPGM->width && imagemPGM->matrizP2[i][j + 1] == atual)
            {

                contador++;
            }
            else
            {
                if (contador > 3)
                {
                    arrayAuxiliar[k] = -10;
                    k++;
                    arrayAuxiliar[k] = imagemPGM->matrizP2[i][j];
                    k++;
                    arrayAuxiliar[k] = contador;
                    k++;
                }
                else
                {
                    for (int l = 0; l < contador; l++)
                    {
                        arrayAuxiliar[k] = imagemPGM->matrizP2[i][j];
                        k++;
                    }
                }
                if (j + 1 < imagemPGM->width)
                {
                    atual = imagemPGM->matrizP2[i][j + 1];
                }
                contador = 1;
            }
            if (j + 1 == imagemPGM->width)
            {
                imagemPGMC->matrizP8[i] = (int *)calloc(sizeof(int), k);
                sizeLines[i] = k;
                for (int m = 0; m < k; m++)
                {
                    imagemPGMC->matrizP8[i][m] = arrayAuxiliar[m];
                }
                k = 0;
            }
        }
    }
    escreverArquivoP8(imagemPGMC, sizeLines, imagemPGMC->height);
}

int main()
{
    FILE* P2;
    imagemP8 imagemPGMC;
    imagemP2 imagemPGM;

    P2 = fopen("C:/Users/Vitor M/Documents/GitHub/trabalho1esdd/matrizP2.txt", "r");
    lerArquivoP2(P2, &imagemPGM);
    compactar(&imagemPGM, &imagemPGMC);
    return 0;
}
