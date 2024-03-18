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

int is_full(t_sorted_list *sortedList) {return sortedList->qtdElem == sortedList->max? 1:0;}
int is_empty(t_sorted_list *sortedList) {return sortedList->qtdElem == 0? 1:0;}

int push(t_sorted_list *sortedList, t_elem elem){
    if(is_full(sortedList)) return 0;

    sortedList ->itens[sortedList->qtdElem] = elem;

    if(sortedList ->qtdElem > 1){
        mergeSort(sortedList->itens, sortedList->itens[0], sortedList->itens[sortedList->max]);
    }
    return 1;
}