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
    imagemPGM->matrizP2 = (int **)malloc(sizeof(int *) * (imagemPGM->height));

    for (int i = 0; i < imagemPGM->height; i++)
    {
        imagemPGM->matrizP2[i] = (int *)malloc(sizeof(int) * (imagemPGM->width));
    }
}

void lerArquivoP2(FILE *P2, imagemP2 *imagemPGM)
{

    P2 = fopen("arquivoP2", "r");
    fscanf(P2, "%s", imagemPGM->magicNumber);
    fscanf(P2, "%d %d", imagemPGM->width, imagemPGM->height);
    fscanf(P2, "%d", imagemPGM->maxGray);

    alocarMatrizP2(imagemPGM);

    for (int i = 0; i < imagemPGM->height; i++)
    {
        for (int j = 0; j < imagemPGM->width; j++)
        {
            fscanf(P2, "%d", imagemPGM->matrizP2[i][j]);
        }
    }

    fclose(P2);
}

void compactar(imagemP2 *imagemPGM, imagemP8 *imagemPGMC)
{
    imagemPGMC->matrizP8 = calloc(sizeof(int *), imagemPGM->height);
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
}
void AlocaMatrizP8(imagemP8 *imagemPGMC)
{
}

int main()
{
    imagemP2 *imagemPGM;


    return 0;
}
