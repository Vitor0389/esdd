
int main(){
    int array[12] = {1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3}; //Array de exemplo
    int *arrayCompactado;
    int size = 0 ; //Calculando tamanho do array
    int k = 0;
    int sizeFinal = 0;

    arrayCompactado = calloc(sizeof(int), 12); // Calloc pra nao dar lixo de memória
    int contador = 1; // contador
    for(int i = 0; i < 12; i++){
        size ++; // Contando quantos elementos tem
        if(i + 1 < 12 && array[i] == array[i + 1]){ // Condição de parada i + 1 < 12 pra ele nao tentar ler o que ta fora do Array.
            contador ++;
        }
        else{
            arrayCompactado[k] = array[i];
            k++;
            arrayCompactado[k] = contador;
            k++;
            contador = 1;
        }
    }
    sizeFinal = size - k;
    arrayCompactado = realloc(arrayCompactado, sizeFinal * sizeof(int));
    
    for(int i = 0;  i < k; i++){
        printf("[%2d]", arrayCompactado[i]);
    }
    free(arrayCompactado);
    return 0;
}