#include <stdio.h>
#include <stdlib.h>

void bad_input(){
	printf("bad input");
	exit(0);
}

void Swap(int *s1, int *s2){
    int tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

void Heapify(int *Array, int N, int i){
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < N && Array[left] > Array[max]){
        max = left;
    }

    if(right < N && Array[right] > Array[max]){
        max = right;
    }
        if (max != i){
        Swap(&Array[i], &Array[max]);
        Heapify(Array, N, max);
    }
}

void Heap(int *Array, int N){
    for (int i = N / 2 - 1; i >= 0; --i){
        Heapify(Array, N, i);
    }
    for (int i = N - 1; i >= 0; --i){
        Swap(&Array[0], &Array[i]);
        Heapify(Array, i, 0);
    }

}

int main(){
    int N;
    if (scanf("%i", &N) == 0){
        bad_input();
    }

    int *Array = (int*) malloc(sizeof(int) * N);
    for (int i = 0; i < N; ++i){
        if (scanf("%i", &Array[i]) == 0){
            free(Array);
            bad_input();
        }
    }

    Heap(Array, N);

    for (int i = 0; i < N; ++i)
        printf("%i ", Array[i]);

    free(Array);
    return 0;
}
