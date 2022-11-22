#include <stdio.h>
#include <string.h>
int E(), Edash();
char *ip;
char string[50];
int main()
{
    printf("Enter the string\n");
    scanf("%s", string);
    ip = string;
    printf("\n\nInput\tAction\n--------------------------------\n");

    if (E() && *ip == '\0')
    {
        printf("\n--------------------------------\n");
        printf("\n String is successfully parsed\n");
    }
    else
    {
        printf("\n--------------------------------\n");
        printf("Error in parsing String\n");
    }
}
int E()
{
    printf("%s\tE->iE' \n", ip);
    if (*ip == 'i')
    {
        ip++;
        if (Edash())
        {
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}
int Edash()
{
    if (*ip == '+' && *(ip + 1) == 'i')
    {
        printf("%s\tE'->+iE' \n", ip);
        ip++;
        ip++;

        if (Edash())
        {
            return 1;
        }
        else
            return 0;
    }

    else
    {
        printf("\tE'->^ \n");
        ip++;
        return 1;
    }
}
