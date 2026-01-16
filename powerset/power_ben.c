#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ac;
char **av;
int target;
int solution = 0;
int *subset;
int subsetlen;
void print()
{
    for(int i = 0;i<subsetlen;i++)
    {
        solution = 1;
        if(i > 0)
            printf(" ");
        printf("%d",subset[i]);
    }
    printf("\n");
}
int sum()
{
    int sum = 0;
    for(int i = 0;i<subsetlen;i++)
    {
        sum = sum + subset[i];
    }
    return (sum);
}

void find(int start)
{
    if (subsetlen != 0 && sum() == target)
        print();
    for(int i = start;i<ac;i++)
    {
        subset[subsetlen++] = atoi(av[i]);
        find(i+1);
        subsetlen--;
    }

}
int main(int argc,char *argv[])
{
    if (argc <= 2)
        return (1);
    ac = argc;
    av = argv;
    int buf[ac-2];
    subset = buf;
    target = atoi(av[1]);
    find(2);
    if (!solution)
        printf("\n");
}