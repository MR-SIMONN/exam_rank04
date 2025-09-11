
#include "../../header.h"

char *s;

int parsesum();
int parseproduct();
int parsefactor();


void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
}

int check_input(char *str)
{
    int par = 0;
    int i = 0;
    while (str[i])
    {
        if (str[i] == '(')
            par++;
        if (str[i] == ')')
            par--;
        i++;
    }
    i = 0;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9' && str[i + 1] >= '0' && str[i + 1] <= '9')
            return (unexpected(str[i + 1]), 1);
    }
    if (par > 0)
        return (unexpected('('), 1);
    else if (par < 0)
        return (unexpected(')'), 1);
    i = 0;
    while (str[i])
    {
        if ((str[i] == '+' || str[i] == '*') && str[i + 1] == '\0')
            return (unexpected(0), 1);
        i++;
    }
    return 0;
}

int parsesum()
{
    int sum1 = parseproduct();
    int sum2;
    while (*s == '+')
    {
        s++;
        sum2 = parseproduct();
        sum1 = sum1 + sum2;
    }
    return sum1;
}

int parseproduct()
{
    int multi1 = parsefactor();
    int multi2 ;
    while (*s == '*')
    {
        s++;
        multi2 = parsefactor();
        multi1 = multi1 * multi2;
    }
    return multi1;
}

int parsefactor()
{
    int nb;
    if (*s >= '0' && *s <= '9')
        return (*s++ - '0');
    else if (*s == '(')
    {
        s++;
        nb = parsesum();
        s++;
    }
    return nb;
}

int main (int ac, char **av)
{
    (void)ac;
    s = av[1];
    if (check_input(av[1]))
        return 1;
    int result = parsesum();
    printf ("%d", result);
}