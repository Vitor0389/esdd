#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    char magicNumber[3];
    int width, height;
    int maxGray;
    int *matrizP2;
} imagemP2;

void alocarMatrizP2(imagemP2 *imagemPGM)
{
    imagemPGM->matrizP2 = calloc(sizeof(int), (imagemPGM->width * imagemPGM->height));
}

void lerArquivoP2(FILE *P2, imagemP2 *imagemPGM)
{

    P2 = fopen("arquivoP2", 'r');
    fscanf(P2, "%s", imagemPGM->magicNumber);
    fscanf(P2, "%d %d", imagemPGM->width, imagemPGM->height);
    fscanf(P2, "%d", imagemPGM->maxGray);

    alocarMatrizP2(imagemPGM);

    for (int i = 0; i < imagemPGM->height; i++)
    {
        for (int j = 0; j < imagemPGM->width; j++)
        {
            fscanf(P2, "%d", imagemPGM->matrizP2[i * imagemPGM->width + j]);
        }
    }
}

void compactar(imagemP2 *imagemPGM)
{
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: nome_do_programa <arquivo_de_entrada> <arquivo_de_saida>\n");
        exit(1);
    }
    imagemP2 *imagemPGM;
    char *entrada = argv[1];
    char *saida = argv[2];

    return 0;
}
