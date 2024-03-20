#include <stdio.h>
#include <stdlib.h>

typedef int t_elem;

typedef struct{
    int max;
    int qtdElem;
    int *itens;
} t_sorted_list;


void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}


t_sorted_list* create_list(int qtd){
    t_sorted_list *sortedList = (t_sorted_list*)malloc(sizeof(t_sorted_list));

    sortedList->max = qtd;
    sortedList->qtdElem = 0;
    sortedList->itens = (t_elem*)malloc(qtd * sizeof(t_elem));
}

int is_empty(t_sorted_list *sortedList) {return sortedList->qtdElem == 0? 1:0;}

void append(t_sorted_list *sortedList, t_elem elem){
    sortedList ->itens[sortedList->qtdElem++] = elem;

    if(sortedList ->qtdElem > 1){
        mergeSort(sortedList->itens, sortedList->itens[0], sortedList->itens[sortedList->max]);
    }

    if(sortedList ->qtdElem > sortedList ->max){
        (t_sorted_list*)realloc(sortedList ->itens, sortedList->qtdElem * sizeof(t_elem));
    }
}

void print_list(t_sorted_list *sortedList){
    for(int i = 0; i < sortedList ->qtdElem; i++){
        printf("Elemento[%d] : [%d]", sortedList->qtdElem, sortedList->itens[i]);
    }
}


void remove_by_index(t_sorted_list *sortedList, int index){}

void remove_by_element(t_sorted_list *sortedList, t_elem elem){}

int index_of(t_sorted_list *sortedList, t_elem elem){}

int get_index(t_sorted_list *sortedList, int index){}

int count(t_sorted_list *sortedList, t_elem elem){}

int len(t_sorted_list *sortedList) {}

void clear(t_sorted_list *sortedList){}