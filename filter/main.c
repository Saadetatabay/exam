#include <string.h>
# include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	int size = 0;
	char *tmp;
	int len = strlen(argv[1]);
	char *text = calloc(len,sizeof(char));
	if (!text)
	{
		perror("Error : \n");
		return (1);
	}
	char c;
	while(read(0,&c,1) > 0)
	{
		tmp = realloc(text,size + 2);
		if (!tmp)
		{
			free(text);
			perror("Error: \n");
			return (1);
		}
		text = tmp;
		text[size] = c;
		text[size + 1] = '\0';
		size ++;
	}
	int j;
	int i = 0;
	while(i<size)
	{
		j = 0;
		while(j<len && i+j<size && text[i+j] == argv[1][j])
			j++;
		if (j == len)
		{
			while(j--)
				printf("*");
			i = i + len -1;
		}
		else
			printf("%c",text[i]);
		i++;
	}
	free(text);
	return (0);
}