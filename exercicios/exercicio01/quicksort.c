#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void quicksort(int data[], int tam);
void _qsort(int data[], int p, int r);
int partition(int data[], int p, int r);
void swap(int data[], int p1, int p2);

void quicksort(int data[], int tam)
{
    _qsort(data, 0, tam-1);
}

void _qsort(int data[], int p, int r) {
    if(p < r) {
        int q = partition(data,p, r);
        _qsort(data, p, q-1);
        _qsort(data, q+1, r);
    }
}

int partition(int data[], int p, int r) {
    int q = p;
    for(int j=p; j<r; j++) {
        if(data[j] <= data[r]) {
            swap(data,j,q);
            q++;
        }
    }
    swap(data,r,q);
    return q;
}

void swap(int data[], int p1, int p2) {
    int tmp = data[p1];
    data[p1] = data[p2];
    data[p2] = tmp;
}

int main()
{
    for(int tam =10000; tam<100000; tam+10000){
    
    int data[tam];

    for(int i=0; i<tam; i++)
        data[i] = rand()%(tam*10);

    long start = clock();
    quicksort(data, tam);
    long end = clock();
    printf("Random com %d elementos: %ld ns\n", tam, (end-start));


    for(int i=0; i<tam; i++)
        data[i] = i;

    start = clock();
    quicksort(data, tam);
    end = clock();
    printf("Crescente com %d elementos: %ld ns\n", tam, (end-start));


    for(int i=0; i<tam; i++)
        data[i] = tam-1-i;

    start = clock();
    quicksort(data, tam);
    end = clock();
    printf("Decrescente com %d elementos: %ld ns\n", tam, (end-start));

    //for(int i=0; i<tam; i++)
    //    printf("%5d", data[i]);
    //printf("\n");
    
    } 
}
