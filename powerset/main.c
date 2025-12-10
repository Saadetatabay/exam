#include <stdio.h>
#include <stdlib.h>

void is_subset(int count,int substoplam,int *ar)
{
    
}

int main(int argc,char *argv[])
{
    if (argc < 3)
        return 0;
    int i = 0;
    int subs_toplam = atoi(argv[1]); //subsettoplamı olması gerek
    int count = argc - 2;
    int num[count];
    while (i < count)
    {
        num[i] = atoi(argv[i+2]);
        i++;
    }
    is_subset(count,subs_toplam,num);
}