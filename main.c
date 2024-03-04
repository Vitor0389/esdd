#include <stdio.h>
#include <stdlib.h>
typedef struct{
    char magicNumber[3];
    int width, height;
    int maxGray;
    int matrizP2[][];
} imagemP2;

void lerArquivoP2(FILE *P2){
        

}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: nome_do_programa <arquivo_de_entrada> <arquivo_de_saida>\n");
        exit(1);
    }

    char *entrada = argv[1];
    char *saida = argv[2];


    return 0;
}


