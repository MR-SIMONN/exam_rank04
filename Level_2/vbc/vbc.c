
#include <stdio.h>

char *s;

int parsesum();
int parseproduct();
int parsefactor();


void unexpected(char c)
{
    if (c == 'x')
        printf("Unexpected end of input\n");
    else
        printf("Unexpected token '%c'\n", c);
}

int parse_input(char *str)
{
    int i = 0;
    int parentese = 0;
    while (str[i])
    {
        if (str[i] == '(')
            parentese++;
        if (str[i] == ')')
            parentese--;
        i++;
    }
    if (parentese > 0)
    {
        unexpected('(');
        return 1;
    }
    else if (parentese < 0)
    {
        unexpected(')');
        return 1;
    }
    i = 0;
    while( str[i])
    {
        if ((str[i] >= '0' && str[i] <= '9') && (str[i + 1] >= '0' && str[i + 1] <= '9'))
        {
            unexpected(str[i + 1]);
            return 1;
        }
        if ((str[i] == '*' || str[i] == '+') && str[i + 1] == '\0')
        {
            unexpected('x');
            return 1;
        }
        i++;
    }
    return 0;
}

int parsesum()
{   
    int pro1 = parseproduct();
    int pro2;
    while(*s == '+')
    {
        s++;
        pro2 = parseproduct();
        pro1 = pro1 + pro2;
    }
    return (pro1);
}

int parseproduct()
{
    int fac1 = parsefactor();
    int fac2;
    while (*s == '*')
    {
        s++;
        fac2 = parsefactor();
        fac1 = fac1 * fac2;
    }
    return fac1;
}

int parsefactor()
{
    int sum;
    if (*s >= '0' && *s <= '9')
        return (*s++ -'0');
    else if (*s == '(')
    {
        s++; // to skip '('
        sum = parsesum();
        s++; // to skip ')'
    }
    return (sum);
}

int main(int ac, char **av)
{
    (void)ac;
    s = av[1];
    if (parse_input(av[1]))
        return 1;
    int result = parsesum();
    printf("%d", result);
    return (0);
}