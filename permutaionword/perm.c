#include "perm.h"
int ft_strlen(char *s)
{
    if (!s)
        return (0);
    int i = 0;
    while(s[i])
        i++;
    return (i);
}
void swap(char *a,char *b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void sort_args(char *arg)
{
    int j;
    int len = ft_strlen(arg);
    while (len--)
    {
        j = 0;
        while (arg[j+1])
        {
            if (arg[j] > arg[j +1])
                swap(arg + j,arg + j +1);
            j++;
        }
    }
}

void permute(char *s,int start,int end)
{
    if (start == end)
        puts(s);
    else
    {
        int i = start;
        while (i < end)
        {
            sort_args(s + start);
            swap(s +start,s+i);
            permute(s,start + 1,end);
            swap(s +start,s+i);
            i++;
        }
    }
}

int main(int agrc,char *argv[])
{
    if (agrc != 2)
        return (1);
    int len = ft_strlen(argv[1]);
    permute(argv[1],0,len);
}