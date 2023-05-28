#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define ALPHABET_SIZE 256
#define TEMPLATE_SIZE 17
#define BUFFER_SIZE 4096

#define uc unsigned char

int ReadTemplate(uc *template, FILE *in)
{
    int length = 0;
    uc get;
    while (fread(&get, sizeof(uc), 1, in) == 1 && get != '\n')
    {   template[length] = get;
        length += 1;
    }
    template[length] = '\0';
    return (length);
}

void BoyerMoore(FILE *out, uc *buffer, uc *template, int *shiftTable, int32_t *globalShift)
{
    int bufLen = strlen((char *)buffer);
    int tempLen = strlen((char *)template);
    int32_t shift = 0;
    while (shift <= (bufLen - tempLen))
    {
        int cur = tempLen - 1;
        while (cur >= 0 && template[cur] == buffer[shift + cur])
        {
            fprintf(out, "%i ", *globalShift + shift + cur + 1);
            cur--;
        }
        if (cur < 0)
        {
            shift += (shift + tempLen < bufLen) ? tempLen : 1;
        }
        else
        {
            fprintf(out, "%i ", *globalShift + shift + cur + 1);
            shift += shiftTable[buffer[shift + tempLen - 1]];
        }
    }
    (*globalShift) += shift;
}

int *FillShiftTable(uc *template, int templateLen)
{
    int *shiftTable = malloc(ALPHABET_SIZE * sizeof(int));
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        shiftTable[i] = templateLen;
    }
    for (int i = 0; i < templateLen - 1; ++i)
    {
        shiftTable[(int)template[i]] = templateLen - i - 1;
    }
    return (shiftTable);
}

int main()
{
    FILE *in = fopen("in.txt", "r");

    uc template[TEMPLATE_SIZE];
    int templateLen = ReadTemplate(template, in);
    int *shiftTable = FillShiftTable(template, templateLen);
    uc *buffer = malloc((BUFFER_SIZE + 1) * sizeof(uc));
    int bufferLen = fread(buffer, sizeof(uc), BUFFER_SIZE, in);

    FILE *out = fopen("out.txt", "a+");
    int32_t globalShift = 0;

    while (bufferLen == BUFFER_SIZE)
    {
        buffer[BUFFER_SIZE] = '\0';
        BoyerMoore(out, buffer, template, shiftTable, &globalShift);
        memset(buffer, 0, BUFFER_SIZE);
        bufferLen = fread(buffer, sizeof(uc), BUFFER_SIZE, in);
    }
    buffer[bufferLen] = '\0';

    BoyerMoore(out, buffer, template, shiftTable, &globalShift);

    free(shiftTable);
    free(buffer);
    fclose(in);
    fclose(out);
    return 0;
}
