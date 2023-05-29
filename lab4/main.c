#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STACK 2048
#define MAX_EXPRESSION 2048

void SyntaxError(){
    printf("syntax error");
    exit(0);
}

void DivisionByZero(){
    printf("division by zero");
    exit(0);
}

typedef struct Stack{ //operators stack
    char stack[MAX_STACK];
    int stack_len;
    int priority[MAX_STACK];
} Stack;

void Init(Stack *st){
    st->stack_len = 0;
}

int DefinePriority(char *in, int i){ //setting the priority of operations
    int priority = 0;
    if (in[i] == '+' || in[i] == '-') {priority = 0;}
    else if(in[i] == '*' || in[i] == '/') {priority = 1;}
    else if(in[i] == '(') {priority = -1;}

    return priority;
}

void Push(Stack *st, char *in, int i){
    st->priority[st->stack_len] = DefinePriority(in, i);
    st->stack[st->stack_len] = in[i];
    st->stack_len++;
}

void Pop(Stack *st, char *exp, int e_len){
    exp[e_len] = st->stack[st->stack_len - 1];
    st->stack_len--;
}

void CheckIn(char *in, int i){
    if (!isdigit(in[i]) && in[i] != '+' && in[i] != '-' && in[i] != '*' && in[i] != '/' && in[i] != '(' && in[i] != ')'){
        SyntaxError();
    }
}

void CountBrackets(int *countBrackets, char *in, int i){
    int cBrackets = 0;
    if (in[i] == '(') {cBrackets += 1;}
    else if(in[i] == ')') {cBrackets -= 1;}
    *countBrackets += cBrackets;
    if (*countBrackets < 0) {SyntaxError();}
}

void CheckCountBrackets(int count){
    if (count != 0) {SyntaxError();}
}

void CheckDoubleBrackets(char *in, int i){
    if(in[i] == '(' && in[i + 1] == ')') {SyntaxError();}
    else if(in[i] == ')' && in[i + 1] == '(') {SyntaxError();}
}

int CharToInt(char digit){
    return digit - '0';
}

void FindVars(char *exp, int i, int *first, int *second){
    int f = -1, s = -1;
    for (int j = i; j >= 0; --j){
        if (exp[j] == 'a' && s != -1){
            f = j;
            break;
        }
        if (exp[j] == 'a') {s = j;}
    }
    if (f == -1 || s == -1) {SyntaxError();}
    *first = f;
    *second = s;
}

void Convert(char *in, int inLen, int *countBrackets, Stack *st, char *exp, int *e_len, int *digits){ //converting to reverse polish notation
    int eLen = 0; //e_len
    int cBrackets = 0; //countBrackets
    for (int i = 0; i < inLen; ++i){
        CheckIn(in, i);
        if (in[i] == '(' || in[i] == ')'){
            CountBrackets(&cBrackets, in, i);
            CheckDoubleBrackets(in, i);
        }
        if (!isdigit(in[i])){
            if (in[i] != ')'){
                if (st->stack_len == 0){
                    Push(st, in, i);
                }
                else{
                    while(st->priority[st->stack_len - 1] >= DefinePriority(in, i) && st->stack_len > 0 && in[i] != '('){
                        Pop(st, exp, eLen);
                        eLen++;
                    }
                    Push(st, in, i);
                }
            }
            else{
                while (st->stack[st->stack_len - 1] != '('){
                    Pop(st, exp, eLen);
                    eLen++;
                }
                st->stack_len--;
            }
        }
        else{
            int digit = 0;
            exp[eLen] = 'a'; //the place in the expression where the number should stand
            while (isdigit(in[i])){
                digit *= 10;
                digit += CharToInt(in[i]);
                i++;
            }
            digits[eLen] = digit;
            eLen += 1;
            i--;
        }
    }
    while (st->stack_len > 0){
        Pop(st, exp, eLen);
        eLen += 1;
    }
    *e_len = eLen;
    *countBrackets = cBrackets;
}

int Calculations(int e_len, char *exp, int *digits){ //making calculations
    int pos = 0;
    for (int i = 0; i < e_len; ++i){
        if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/'){
            int first, second;
            FindVars(exp, i, &first, &second);
            if (exp[i] == '+'){
                digits[i] = digits[first] + digits[second];
            }
            else if (exp[i] == '-'){
                digits[i] = digits[first] - digits[second];
            }
            else if (exp[i] == '*'){
                digits[i] = digits[first] * digits[second];
            }
            else if (exp[i] == '/'){
                if (digits[second] == 0){
                    DivisionByZero();
                }
                digits[i] = digits[first] / digits[second];
            }
            exp[i] = 'a';
            exp[first] = ' ';
            exp[second] = ' ';
            pos = i;
        }
    }
    return pos;
}
int main(){
    char in[MAX_EXPRESSION]; //in -- input data
    char exp[MAX_EXPRESSION]; //final expression
    int digits[MAX_EXPRESSION]; //array with numbers from the input data
    int e_len = 0; //length of the "exp" array
    if (fgets(in, MAX_EXPRESSION, stdin) == NULL){
        SyntaxError();
    };
    int inLen = strlen(in) - 1;
    if (inLen <= 0){
        SyntaxError();
    }

    Stack stack;
    Init(&stack);

    int countBrackets = 0;

    Convert(in, inLen, &countBrackets, &stack, exp, &e_len, digits);

    CheckCountBrackets(countBrackets); //counting brackets

    int pos = Calculations(e_len, exp, digits); //pos -- the position in array where the answer is stored
    printf("%i", digits[pos]);
}
