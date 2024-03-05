
int main(){
    int array[12] = {1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3}; //Array de exemplo
    int *arrayCompactado;
    int k = 0;

    arrayCompactado = calloc(sizeof(int), 12);
    int contador = 1; // contador
    for(int i = 0; i < 12; i++){
        if(i + 1 < 12 && array[i] == array[i + 1]){
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
    for(int i = 0;  i < k; i++){
        printf("[%2d]", arrayCompactado[i]);
    }
    free(arrayCompactado);
    return 0;
}