#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFF_SIZE 4096
#define TEMPLATE_SIZE 17

typedef unsigned char uc;

int ReadTemplate(uc *template, FILE *in)
{
    int length = 0;
    uc get;
    while (fread(&get, sizeof(uc), 1, in) == 1 && get != '\n')
    {
        template[length] = get;
        length += 1;
    }
    template[length] = '\0';
    return (length);
}

int GetBuffer(int templateLen, uc *symbols, uc *buff, FILE *in)
{
    if (strlen((char *)symbols) != 0)
    {
        for (int i = 0; i < templateLen; i++)
        {
            buff[i] = symbols[i];
        }
    }
    for (int i = 0; i < BUFF_SIZE - TEMPLATE_SIZE; i++)
    {
        uc chr = fgetc(in);
        if (!feof(in))
        {
            buff[templateLen + i] = chr;
        }
        else
        {
            return 1;
        }
    }
    for (int i = BUFF_SIZE - TEMPLATE_SIZE; i < BUFF_SIZE - TEMPLATE_SIZE + templateLen; i++)
    {
        symbols[i - BUFF_SIZE + TEMPLATE_SIZE] = buff[i];
    }
    return 0;
}

void MakePrefixes(uc *str, int *prefixes)
{
    int i = 1;
    int j = 0;
    int len = strlen((const char *)str);
    while (i < len)
    {
        if (str[i] == str[j])
        {
            prefixes[i] = j + 1;
            i++;
            j++;
        }
        else if (j == 0)
        {
            prefixes[i] = 0;
            i++;
        }
        else
        {
            j = prefixes[j - 1];
        }
    }
}

void KMP(FILE *in, int templateLen, int *prefixes, uc *template, uc *remainingSymbols, int64_t *globalIndex)
{
    uc buffer[BUFF_SIZE];
    int index = templateLen;

    while (1)
    {
        int flag = GetBuffer(templateLen, remainingSymbols, buffer, in);
        int bufferLen = strlen((char *)buffer + templateLen);

        while (index <= bufferLen)
        {
            int counter = 0;
            if (buffer[index + counter] == template[counter])
            {
                while (counter < templateLen && buffer[index + counter] == template[counter])
                {
                    counter++;
                }
                printf("%li %i ", (*globalIndex) + index - templateLen + 1, counter);
            }
            if (counter >= 1)
            {
                index += (counter - prefixes[counter - 1]);
            }
            else
            {
                index++;
            }
        }
        (*globalIndex) += BUFF_SIZE - TEMPLATE_SIZE;
        index = index - BUFF_SIZE + TEMPLATE_SIZE;
        memset(buffer, '\0', BUFF_SIZE);
        if (flag)
        {
            break;;
        }

    }
}

int main()
{
    FILE *in = fopen("in.txt", "r");

    uc template[TEMPLATE_SIZE];
    int templateLen = ReadTemplate(template, in);
    if (templateLen == 0)
    {
        fclose(in);
        return 0;
    }

    int *prefixes = calloc(templateLen, sizeof(int));
    MakePrefixes(template, prefixes);

    for (int i = 0; i < templateLen; i++)
    {
        printf("%d ", prefixes[i]);
    }
    printf("\n");

    int64_t globalIndex = 0;
    uc remainingSymbols[TEMPLATE_SIZE];

    KMP(in, templateLen, prefixes, template, remainingSymbols, &globalIndex);

    fclose(in);
    free(prefixes);
    return 0;
}
