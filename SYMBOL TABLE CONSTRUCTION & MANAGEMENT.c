#include <stdio.h>
#include <string.h>
#include <ctype.h>

int bitFormat(int iNumber) // for printing a decimal number in 8 bit binary form
{
    int arrDig[8] = {128, 64, 32, 16, 8, 4, 2, 1};
    int arrCheck[8];
    int i;
    printf("\t\t");
    if (iNumber < 0 || iNumber > 255)
    {
        return 0;
    }
    else
    {
        for (i = 0; i < 8; i++)
        {
            if (iNumber >= arrDig[i])
            {
                arrCheck[i] = 1;
                iNumber = iNumber - arrDig[i];
            }
            else
            {
                arrCheck[i] = 0;
            }
        }
        for (i = 0; i < 8; i++)
            printf("%d", arrCheck[i]);
    }
    return 1;
}

int main()
{
    char input[1000];
    int j = 0;
    int binary = 0;
    char buffer[100];
    int i = 0;
    printf("\n Enter input program in C [with space separated tokens]:");
    scanf("%s", input);
    printf("\n***** SYMBOL TABLE MANAGEMENT *****");
    printf("\n Type \t Size \t Name \t Value \t\t Address \n");
    printf("\n -----\t-----\t------\t-------\t\t---------- \n");
    while (1) // for reading input character by character
    {
        if (input[j] == '\n')
        {
            printf("\n ------------------------------------------------- \n");
            printf("\n SYMBOL TABLE HAS BEEN GENERATED \n");
            break;
        }
        if (input[j] != ' ')
        {
            buffer[i] = input[j];
            i++;
            j++;
        }
        else
        {
            buffer[i] = '\0';
            j++;
        }
        if (strcmp(buffer, "int") == 0)
        {
            // Type \t Size \t Name \t Value \t Address
            printf("\n %s \t %d \t ", buffer, (int)sizeof(int));
            i = 0;
            while (1)
            {
                if (input[j] != '=')
                {
                    buffer[i] = input[j];
                    j++;
                    i++;
                }
                else
                {
                    buffer[i] = '\0';
                    printf("%s", buffer);
                    j++;
                    break;
                }
            }
            i = 0;
            while (1)
            {
                if (input[j] != ';')
                {
                    buffer[i] = input[j];
                    j++;
                    i++;
                }
                else
                {
                    buffer[i] = '\0';
                    printf("\t %s", buffer);
                    j++;
                    break;
                }
            }
            bitFormat(binary);
            binary = binary + sizeof(int);
            i = 0;
            printf("\n");
        }
        else if (strcmp(buffer, "char") == 0)
        {
            // Type \t Size \t Name \t Value \t Address
            printf("\n %s \t %d \t", buffer, (int)sizeof(char));
            i = 0;
            while (1)
            {
                if (input[j] != '=')
                {
                    buffer[i] = input[j];
                    j++;
                    i++;
                }
                else
                {
                    buffer[i] = '\0';
                    printf("%s", buffer);
                    j++;
                    break;
                }
            }
            i = 0;
            while (1)
            {
                if (input[j] != ';')
                {
                    buffer[i] = input[j];
                    j++;
                    i++;
                }
                else
                {
                    buffer[i] = '\0';
                    printf("\t %s", buffer);
                    j++;
                    break;
                }
            }
            bitFormat(binary);
            binary = binary + sizeof(char);
            i = 0;
            printf("\n");
        }
        else
        {
            // printf("\n NO MATCH FOUND ERROR");
        }
    }
    return 0;
}
