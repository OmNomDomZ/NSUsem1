#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <stdint.h>

typedef enum
{
    SUCCESS,
    BAD_INPUT,
    OVERFLOW
}ExitCodes;

char *ExitMessage[] =
{
    "",
    "bad input",
    "overflow"
};

int CheckNum(int *num)
{
    if (scanf("%i", num) != 1)
    {
        return (BAD_INPUT);
    }
    if ((*num) < 1 || (*num) > 10)
    {
        return (BAD_INPUT);
    }
    return (SUCCESS);
}

int CheckCurNum(int64_t *curNum)
{
    if (scanf("%ld", curNum) != 1)
    {
        return (BAD_INPUT);
    }
    if ((*curNum) < INT_MIN || (*curNum) > INT_MAX)
    {
        return (BAD_INPUT);
    }
    return SUCCESS;
}

int CheckSum(int64_t sum)
{
    if (sum < INT_MIN || sum > INT_MAX)
    {
        return (OVERFLOW);
    }
    return (SUCCESS);
}

int main(void)
{
    int num;
    ExitCodes rc;
    if ((rc = CheckNum(&num)) != SUCCESS)
    {
        printf("%s", ExitMessage[rc]);
        return 0;
    }

    int64_t curNum;
    int64_t sum = 0;
    for (int i = 0; i < num; ++i)
    {
        if ((rc = CheckCurNum(&curNum)) != SUCCESS)
        {
            printf("%s", ExitMessage[rc]);
            return 0;
        }
        sum += curNum;
    }

    if ((rc = CheckSum(sum)) != SUCCESS)
    {
        printf("%s", ExitMessage[rc]);
        return 0;
    }
    printf("%ld", sum);
}
