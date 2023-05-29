#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void bad_input(){
    printf("bad input");
    exit(0);
}

void swap(char *a, char *b){
    char tmp = *a;
    *a = *b;
    *b = tmp;
}



void CheckInputStr(char *Sequence, int Len){
    for (int i = 0; i < Len; ++i){
        if(isdigit(Sequence[i]) == 0){
            bad_input();
        }
    }

    for (int i = 0; i < Len; ++i){
        for (int j = i + 1; j < Len; ++j){
            if (Sequence[i] == Sequence[j]){
                bad_input();
            }
        }
    }
}


void reverse(char str[], int Point_Max){
	int lenght = strlen(str);
	for(int first = Point_Max + 1, last = lenght - 1, support = 0; first < last; first++, last--){

		support = str[first];
		str[first] = str[last];
		str[last] = support;
	}
}



int MakeNextPermutation(char *Sequence, int Len){
    int PointMax = Len - 1; //the number of the maximum element in the array
    int MAX = 0; //maximum element in the array standing in front of a larger element

    int suitElements = 0;
    for (int i = 0; i < Len; ++i){
        if((Sequence[i] < Sequence[i + 1])){
            MAX = Sequence[i];
            PointMax  = i;
            suitElements += 1;}
        }

    if (suitElements != 0){
        int Point_L = 0; //the number of the element larger than max and standing after it
        for(int i = PointMax + 1; i < Len; ++i){
            if(Sequence[i]> MAX){
                Point_L = i;
            }
        }
        swap(&Sequence[PointMax], &Sequence[Point_L]);

        reverse(Sequence, PointMax);

        return 1;
    }
    else{
        return 0;
    }
}


int main(){
    char Sequence[100];
    if(fgets(Sequence, 100, stdin) == NULL){
        bad_input();
    }

    int Len = strlen(Sequence) - 1;
    Sequence[Len] = '\0';

    CheckInputStr(Sequence, Len);

    long long N;
    if(scanf("%lld", &N) == 0){
        bad_input();
    }

    if (N < 0){
        bad_input();
    }


    for (; N > 0; --N){

        int gotIt = MakeNextPermutation(Sequence, Len);
        if (gotIt == 1){
            printf("%s\n", Sequence);
        }
        else{
            break;
        }
    }
    return 0;
}
