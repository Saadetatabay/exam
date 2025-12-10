#include <stdio.h>
#include <stdlib.h>

void print_array(int temp_arr[], int size) {
    printf("COZUM: [ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", temp_arr[i]);
    }
    printf("]\n");

}

void is_subset(int count,int substoplam,int ar[],int temp_arr[],int size,int temp_toplam,int indis)
{
    int i;
    if (temp_toplam == substoplam)
    {
        print_array(temp_arr,size);
        //return ;
    }
    i = indis;
    while (i < count)
    {
        temp_arr[size] = ar[i]; // ilk elemanı ekledik
    
        is_subset(count,substoplam,ar,temp_arr,size+1,temp_toplam+ar[i],i+1);
        i++;
    }
}

int main(int argc,char *argv[])
{
    if (argc < 3)
        return 0;
    int i = 0;
    int subs_toplam = atoi(argv[1]); //subsettoplamı olması gerek
    int count = argc - 2;
    int num[count];
    int temp_dizei[count];
    while (i < count)
    {
        num[i] = atoi(argv[i+2]);
        i++;
    }
    is_subset(count,subs_toplam,num,temp_dizei,0,0,0);
}