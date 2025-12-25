#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
    if (argc!= 2 || argv[1][0] == '\0')
        return(1);
    
    int size = 0;
    char c;
    int len = strlen(argv[1]);
    char *text = calloc(len,sizeof(char));
    if (!text)
    {
        perror("error");
        return(1);
    }
    while(read(0,&c,1)> 0)
    {
        char *temp = realloc(text,size+2);
        if (!temp)
        {
            perror("error");
            free(text);
            return(1);
        }
        text = temp;
        text[size] = c;
        text[size + 1] = '\0';
        size ++;
    }
    int j;
    int i = 0;
    while(i < size)
    {
        j = 0;
        while (j<len && i+j<size)
        {
            if (text[i+j] != argv[1][j])
                break;
            j++;
        }
        if (j == len)
        {
            while(j--)
                printf("*");
            i = i +len-1;
        }
        else 
        {
            printf("%c",text[i]);
        }
        i++;
    }
    free(text);
    return(0);
}