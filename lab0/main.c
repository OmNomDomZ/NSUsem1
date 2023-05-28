#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void ToLower(char *InputValue){
	for (size_t i = 0; i < strlen(InputValue); ++i){
		InputValue[i] = tolower(InputValue[i]);
	}
}


void bad_input(){
	printf("bad input");
	exit(0);
}

void swap(char *a, char *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int CharToInt(char digit){
	if (isdigit(digit)) {return digit - '0';}
	else if(digit >= 'a' && digit <= 'f') {return digit - 'a' + 10;}
	return -1;
}


void CheckInputValueOrDie(char *InputValue, int b1){
    int countPoint = 0;

	if (InputValue[0] == '.' || InputValue[strlen(InputValue) - 1] == '.'){
		bad_input();
	}
	for (size_t i = 0; i < strlen(InputValue); ++i){
		if(InputValue[i] == '.'){
			countPoint += 1;
		}
		if (countPoint > 1){
			bad_input();
		}
		if (InputValue[i] == '.'){
			continue;
		}
		if (InputValue[i] >= 'a'){
			int x = InputValue[i] - 'a' + 10;
			if (x >= b1 || x <= 0){
				bad_input();
			}
		}
		else{
			int x = (int)InputValue[i] - '0';
			if (x >= b1 || x < 0){
				bad_input();
			}
		}
	}
}

void ReadFP(long long int *n_, long long int *d_, int b1, int dotPosition, int LEN, char *InputValue){
    long long numerator = 0, denominator = 1;
    for (int i = dotPosition + 1; i < LEN; ++i){
        numerator = numerator * b1;
        numerator = (numerator + CharToInt(InputValue[i]));
    }
    for (int i = 0; i < LEN - dotPosition - 1; ++i){
        denominator *= b1;
    }
    *n_ = numerator;
    *d_ = denominator;
}



void reverse(char str[]){
	int lenght = strlen(str);
	for(int first = 0, last = lenght - 1; first < last; first++, last--){
		if (str[first] == '\0'){
			break;
		}
		swap(&str[first], &str[last]);
	}
}



int main(){
	int b1, b2;
	int d1 = scanf("%d", &b1);
	int d2 = scanf("%d", &b2);
	if ((b1 < 2 || b1 > 16) || (b2 < 2 || b2 > 16) || (d1 != 1) || (d2 != 1)){
		bad_input();
	}

	char InputValue[13 + 1];
	int D = scanf("%13s", InputValue);
	if (D != 1){
		bad_input();
	}

	ToLower(InputValue);

	CheckInputValueOrDie(InputValue, b1);

	long long int IntValue_ConvertedFromB1 = 0;
	long long int numerator = 0;
    long long int denominator = 1;
	int dotPosition = 0;

	int LEN = strlen(InputValue);
	for (int i = 0; i < LEN; ++i){
		if (InputValue[i] == '.'){
			dotPosition = i;
			break;
		}
	}

	if (dotPosition != 0){

		IntValue_ConvertedFromB1 = CharToInt(InputValue[0]);
		for(int i = 1; i < dotPosition; ++i){
			IntValue_ConvertedFromB1 = IntValue_ConvertedFromB1 * b1 + CharToInt(InputValue[i]);
		}
		ReadFP(&numerator, &denominator, b1, dotPosition, LEN, InputValue);
	}
	else{
		IntValue_ConvertedFromB1 = CharToInt(InputValue[0]);
		for(int i = 1; i < LEN; ++i){
			IntValue_ConvertedFromB1 = IntValue_ConvertedFromB1 * b1 + CharToInt(InputValue[i]);
		}
		numerator = 0;
		denominator = 1;
	}


	char IntPartConvert[100]; //IntPartConvert -- integer part of the number after converting to b2
	int kolvo = 0;
	if (IntValue_ConvertedFromB1 == 0){
		IntPartConvert[kolvo] = '0';
		kolvo += 1;
	}
	else{
		while (IntValue_ConvertedFromB1 != 0){
			long long int IntPartOfDiv = IntValue_ConvertedFromB1 / b2; //IntPartOfDiv -- integer part of the devision by b2
			IntValue_ConvertedFromB1 = IntValue_ConvertedFromB1 - IntPartOfDiv * b2;
			if (IntValue_ConvertedFromB1 <= 9 && IntValue_ConvertedFromB1 >= 0){
				IntPartConvert[kolvo] = IntValue_ConvertedFromB1 + '0';
			}
			else if(IntValue_ConvertedFromB1 >= 10 && IntValue_ConvertedFromB1 <= 16){
				IntPartConvert[kolvo] = IntValue_ConvertedFromB1 - 10 + 'a';
			}
			IntValue_ConvertedFromB1 = IntPartOfDiv;
			kolvo += 1;
			}
		}
	IntPartConvert[kolvo] = '\0';
	reverse(IntPartConvert);


	char Numerator[100];
    int kolvo2 = 0;
	int NUM = 0;
	if (numerator != 0){
		NUM = 1;
	}
    while ((numerator != 0) && (kolvo2 != 12)){
        long long intPart = (numerator * b2) / denominator;
        if (intPart <= 9 && intPart >= 0){
			Numerator[kolvo2] = intPart + '0';
		}
		else if(intPart >= 10 && intPart <= 16){
			Numerator[kolvo2] = intPart - 10 + 'a';
		}
        numerator = (numerator * b2) % denominator;
        kolvo2 += 1;
    }
    Numerator[12] = '\0';



	int length =  kolvo + 1 + 12 + 1;
	char Answer[length];
	for (int i = 0; i < kolvo; ++i){
		Answer[i] = IntPartConvert[i];
	}
	if (NUM != 0){
		Answer[kolvo] = '.';
		int variable = 0;
		for (int i = kolvo + 1; i < (kolvo2 + kolvo + 1); ++i){
			Answer[i] = Numerator[variable];
			variable += 1;
		}
		for (int i = (kolvo2 + kolvo + 1); i < length - 1; ++i){
			Answer[i] = '0';
		}
		Answer[length - 1] = '\0';
	}
	else{
		Answer[kolvo] = '\0';
	}

	printf("%s", Answer);
	return 0;
}
