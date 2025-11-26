#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>



void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of file\n");
    exit(1);
}

int accept(char **s, char c)
{
    if (**s == c)
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

int parse_expression(char**s);
int parse_term(char**s);
int parse_factor(char**s);

int parse_factor(char**s)
{
    if(isdigit(**s))
    {
        int val = **s - '0';
        (*s)++;
        return val;
    }
    if (accept(s,'('))
    {
        int result = parse_expression(s);
        if (!expect(s,')'))
        {
            exit(1);
        }
        return result;
    }
    unexpected(**s);
    return 1;
}

int parse_term(char**s)
{
    int left = parse_factor(s);
    while(accept(s, '*'))
    {
        int right = parse_factor(s);
        left *= right;
    }
    return left;
}
int parse_expression(char**s)
{
    int left = parse_term(s);
    while(accept(s, '+'))
    {
        int right = parse_term(s);
        left += right;
    }
    return left;
}
int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    char *s = argv[1];
    if (!s)
    {
        unexpected(0);
    }
    int result = parse_expression(&s);
    if(*s)
    {
        unexpected(*s);
    }
    printf("%d\n",result);
    return 0;
}