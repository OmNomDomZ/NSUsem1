#include <stdlib.h>
#include <stdio.h>

void Bad_input(){
	printf("bad input");
	exit(0);
}

void Swap(int *s1, int *s2){
    int tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

void QuickSort(int *array, int left, int right){
    int middle = array[(left + right) / 2];
    int i = left, j = right;
    if (left < right){
        while(i < j){
            while (array[i] < middle){
                i++;
            }
            while (array[j] > middle){
                j--;
            }
            if (i <= j){
                Swap(&array[i], &array[j]);
                i++;
                j--;
            }
        }

        QuickSort(array, left, j);
        QuickSort(array, i, right);
    }
}
int main(){
    int N;
    if (scanf("%i", &N) == 0){
        Bad_input();
    }
    int *array = (int*) malloc(sizeof(int) * N);
    for (int i = 0; i < N; ++i){
        if (scanf("%i", &array[i]) == 0){
            free(array);
            Bad_input();
        }
    }
    int left = 0, right = N - 1;
    QuickSort(array, left, right);

    for (int i = 0; i < N; ++i){
        printf("%i ", array[i]);
    }
    free(array);
    return 0;
}
