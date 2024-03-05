#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char magicNumber[3];
    int width, height;
    int maxGray;
    int *matrizP2;
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
    imagemPGM->matrizP2 = (int*)malloc(sizeof(int) * (imagemPGM->width * imagemPGM->height));
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
            fscanf(P2, "%d", imagemPGM->matrizP2[i * imagemPGM->width + j]);
        }
    }
}

void compactar(imagemP2* imagemPGM, int matrizP2[][24], int matrizP8[][24]){
	int contador = 1;
	int atual = matrizP2[0][0];
	int k = 0;
	
	for (int i = 0; i < imagemPGM -> height; i++) {
        for (int j = 0; j < imagemPGM -> width; j++) {
        	
            if (imagemPGM -> matrizP2[i][j] == atual && contador <= imagemP2 -> widht) {
                contador++; // Incrementa a contagem se o elemento atual é o mesmo que o anterior
                
            } else{
                if(contador > 3){
                	matrizP8[i][k] = -10;
                	matrizP8[i][k + 1] = atual;
                	matrizP8[i][k + 2] = contador;
                	k += 3;
				} else{
					for(int l = 0; l<contador; l++)
						matrizP8[i][k + l] = matrizP2[i][j];
				}
				contador = 1;
                atual = imagem -> matrizP2[i][j];
            }
        }
        k = 0;
    }
    for(int i = 0; i < 7; i++)
    	for(j = 0; j < 24; j++){
    		printf("%d", matrizP8[i][j]);
		}
}

void main()
{
	int matrizTesteP2[7][24] ={
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 3, 3, 3, 3, 0, 0, 7, 7, 7, 7, 0, 0, 11, 11, 11, 11, 0, 0, 15, 15, 15, 15, 0},
        {0, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 15, 0, 0, 15, 0},
        {0, 3, 3, 3, 0, 0, 0, 7, 7, 7, 0, 0, 0, 11, 11, 11, 0, 0, 0, 15, 15, 15, 15, 0},
        {0, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0},
        {0, 3, 0, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 11, 11, 11, 11, 0, 0, 15, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
        
        int matrizTesteP8[7][24];
        
        compactar(matrizTesteP2, matrizTesteP8);
	
    
}
