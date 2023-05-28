#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#define TEMPLATE_SIZE 17
#define BUFFER_SIZE 4096

#define uc unsigned char

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

int GetHash(uc *str, int len)
{
    int hash = 0;
    for (int i = 0; i < len; i++)
    {
        hash += (((int)str[i]) % 3) * ((int)pow(3, i));
    }
    return (hash);
}

void RabinCarp(uc *template, uc *buf, int32_t *globalShift, int templateHash, int lastDegree, int templateLen)
{
    int bufLen = (int)(strlen((char *)buf));
    int bufHash = GetHash(buf, templateLen);

    for (int i = 0; i <= (bufLen - templateLen); i++)
    {
        if (bufHash == templateHash)
        {
            for (int j = i; j < (i + templateLen); j++)
            {
                if (buf[j] != template[j - i])
                {
                    fprintf(stdout, "%i ", *globalShift + j + 1);
                    break;
                }
                fprintf(stdout, "%i ", *globalShift + j + 1);
            }
        }
        if (i < (bufLen - templateLen))
        {
            bufHash -= ((int)buf[i] % 3);
            bufHash /= 3;
            bufHash += (((int)buf[i + templateLen] % 3) * lastDegree);
        }
    }
    *globalShift += BUFFER_SIZE;
}

int main()
{
    FILE *in = fopen("in.txt", "r");
    uc template[TEMPLATE_SIZE];
    int templateLen = ReadTemplate(template, in);
    uc buffer[BUFFER_SIZE + 1];
    int32_t globalShift = 0;

    int templateHash = GetHash(template, templateLen);
    fprintf(stdout, "%d ", templateHash);
    int lastDegree = (int)pow(3, templateLen - 1);

    int buffer_len = fread(buffer, sizeof(char), BUFFER_SIZE, in);

    while (buffer_len == BUFFER_SIZE)
    {
        buffer[BUFFER_SIZE] = '\0';
        RabinCarp(template, buffer, &globalShift, templateHash, lastDegree, templateLen);
        buffer_len = fread(buffer, sizeof(char), BUFFER_SIZE, in);
    }

    buffer[buffer_len] = '\0';

    RabinCarp(template, buffer, &globalShift, templateHash, lastDegree, templateLen);

    fclose(in);
    return 0;
}
