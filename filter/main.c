#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>
int	filter(char	*s)
{
	int j;
	int i;
	int slen;
	int size;
	char *buffer;
	buffer = malloc(1024);
	if (!buffer) 
	{
    	perror("Error");
    	return 1;
	}
	slen = strlen(s);
	//saaaabcdef   abc
	while ((size = read(0, buffer, 1024))> 0)
	{
		i = 0;
		while (i<size) 
		{
			j = 0;
			while (j < slen && (i + j) < size && buffer[i+j] == s[j])
			{
				j++;
			}
			if (j == slen)
			{
				i = i+j;
				while (j--)
					write(1,"*",1);;
			}
			else
			{
				write(1,&buffer[i],1);
				i++;
			}
		}
	}
	//size = read(0, buffer, 1024);
	if (size < 0) 
	{
    	perror("Error");
    	free(buffer);
    	return 1;
	}
	free(buffer);
	return (0);
}

int main(int argc, char *argv[])
{
	if (argc == 2)
		filter(argv[1]);
	return(1);
}