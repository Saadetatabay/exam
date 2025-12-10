#include "perm.h"

void    permutations(char   *argv)
{
    int len = ft_strlen(argv);
    permute(argv,0,len);
}
void permute (char *s,int indis,int end)
{
    int i;
    if(indis == end)
    {
        puts(s);
        return ;
    }
    i = indis;
    while (i < end)
    {
        // ab olsun indis 0 end 2 
        // i = 0
        // permute(s,1,2)
        //i = 1
        //ab puts
        // i = 1
        //ba permute(s,2,2) ba puts
        swap(&s[indis],&s[i]); // indis başta 0 i ile baştan sona tüm elemanlar 0. indise geliyor
        permute(s,indis+1,end); // 1. konuma geçtik i bu sefer ende kafar tüm sayıları 1. konuma getirdi
        swap(&s[indis],&s[i]);
        i++;
    }
}
void    swap(char *a, char *b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
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