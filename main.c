#include <stdio.h>
#include <stdlib.h>
int **lerArquivoP2(char magicNumber[], int altura, int largura, int maxGray, int **matrizP2)
{
    FILE *P2;
    P2 = fopen("C:/Users/Vitor M/Documents/GitHub/trabalho1esdd/matrizP2.txt", "r");
    if (P2 == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fgets(magicNumber, 4, P2);
    fscanf(P2, "%d %d", &largura, &altura);
    fscanf(P2, "%d", &maxGray);

    matrizP2 = (int **)calloc(sizeof(int *), altura);

    for (int i = 0; i < altura; i++)
    {
        matrizP2[i] = (int *)calloc(sizeof(int), largura);
    }

    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            fscanf(P2, "%d", &matrizP2[i][j]);
        }
        printf("\n");
    }

    fclose(P2);

    return matrizP2;
}
int **lerArquivoP8(char magicNumber[], int altura, int larguraP8, int maxGrayP8, int **matrizP8)
{
    int tamanhoLinhasP8[7], contTamanhoLinhas = 0, pixel, i = 0;
    char caractere;

    FILE *P8;

    P8 = fopen("C:/Users/Vitor M/Documents/GitHub/trabalho1esdd/matrizP8.txt", "r");

    if (P8 == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fgets(magicNumber, 4, P8);
    fscanf(P8, "%d %d", &larguraP8, &altura);
    fscanf(P8, "%d", &maxGrayP8);

    matrizP8 = (int **)calloc(sizeof(int *), altura);

    while ((fscanf(P8, "%d", &pixel)) != EOF)
    {
        if (pixel != '\n')
        {
            contTamanhoLinhas++;
        }
        else
        {
            tamanhoLinhasP8[i] = contTamanhoLinhas;
            i++;
            contTamanhoLinhas = 0;
        }
    }

    for (int i = 0; i < altura; i++)
    {
        matrizP8[i] = (int *)calloc(sizeof(int), tamanhoLinhasP8[i]);
    }

    fclose(P8);

    return matrizP8;
}
void escreverArquivoP8(int **matrizP8, int *sizeLines, int altura, int largura, int maxGray)
{
    FILE *file = fopen("C:/Users/Vitor M/Documents/GitHub/trabalho1esdd/matrizP8.txt", "w");
    char arroba = '@';

    if (file == NULL)
    {
        return;
    }
    fprintf(file, "%s", "P8\n");
    fprintf(file, "%d %d", largura, altura);
    fprintf(file, "\n");
    fprintf(file, "%d", maxGray);
    fprintf(file, "\n");

    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < sizeLines[i]; j++)
        {
            if (matrizP8[i][j] == -10)
            {
                fprintf(file, "%c ", arroba);
            }
            else
            {
                fprintf(file, "%d ", matrizP8[i][j]);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
void escreverArquivoP2(int **matrizP2, int altura, int largura, int maxGray)
{
    FILE *file = fopen("C:/Users/Vitor M/Documents/GitHub/trabalho1esdd/matrizP8.txt", "w");
    char arroba = '@';

    if (file == NULL)
    {
        return;
    }
    fprintf(file, "%s", "P8\n");
    fprintf(file, "%d %d", largura, altura);
    fprintf(file, "\n");
    fprintf(file, "%d", maxGray);
    fprintf(file, "\n");

    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            fprintf(file, "%d", matrizP2[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void compactar(int **matrizP2, int **matrizP8, int altura, int largura, int maxGray)
{
    matrizP8 = (int **)calloc(sizeof(int *), altura);
    int atual = matrizP2[0][0];
    int contador = 1;
    int k = 0;
    int arrayAuxiliar[24];
    int *sizeLines;

    sizeLines = (int *)calloc(sizeof(int), altura);

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
    escreverArquivoP8(matrizP8, sizeLines, altura, largura, maxGray);

    for (int i = 0; i < altura; i++)
    {
        free(matrizP2[i]);
        free(matrizP8[i]);
    }
    free(matrizP2);
    free(matrizP8);
}

void descompactar(int **matrizP2, int **matrizP8, int altura, int largura, int maxGray)
{
    matrizP2 = (int **)calloc(sizeof(int), altura);
    int k = 0;
    int l = 0;
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            if (matrizP8[i][j] == -10)
            {
                k += 2;
                l = matrizP8[i][k];
                k--;
                for (int m = 0; m < l; m++)
                {
                    matrizP2[i][j + m] = matrizP8[i][k];
                }
                k = 0;
            }
            else
            {
                matrizP2[i][j] = matrizP8[i][j];
            }
        }
    }
    escreverArquivoP2(matrizP2, altura, largura, maxGray);

    for (int i = 0; i < altura; i++)
    {
        free(matrizP2[i]);
        free(matrizP8[i]);
    }
    free(matrizP2);
    free(matrizP8);
}

int isP2(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char magicNumber[3];
    fgets(magicNumber, 3, file);
    fclose(file);

    if (strcmp(magicNumber, "P2") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(int argc, char *argv[])
{

    if (argc < 3)
    {
        printf("Uso: %s <arquivo de entrada> <arquivo de saída>\n", argv[0]);
        return 1;
    }
    int **matrizP2;
    int **matrizP8;
    int linhas;
    
    char *arquivo_entrada = argv[1];
    char *arquivo_saida = argv[2];

    if (isP2(arquivo_entrada) && !isP2(arquivo_saida))
    {
        int colunasP2;
        int maxGrayP2;
        char magicNumberP2[3];
        matrizP2 = lerArquivoP2(magicNumberP2, linhas, colunasP2, maxGrayP2, matrizP2);
        compactar(matrizP2, matrizP8, linhas, colunasP2, maxGrayP2);
    }
    else if (isP2(arquivo_saida) && !isP2(arquivo_entrada))
    {
        int colunasP8;
        int maxGrayP8;
        char magicNumberP8[3];
        matrizP8 = lerArquivoP8(magicNumberP8, linhas, colunasP8, maxGrayP8, matrizP8);
        descompactar(matrizP2, matrizP8, linhas, colunasP8, maxGrayP8);
    }

    return 0;
}