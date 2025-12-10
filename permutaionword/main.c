#include <stdio.h>
#include <stdlib.h>

void    permutations(char   *argv)
{
    int len = ft_strlen(argv);
}

int ft_strlen(char *ar)
{
    int i =0;
    if (!ar)
        return 0;
    while(*ar)
    {
        i++;
        ar++;
    }
    return (i);
}

int main(int argc, char *argv[])
{
    if (argc!=2)
        return 0;
    permutations(argv[1]);
}