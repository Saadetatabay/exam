#include "gnl.h"

char *ft_strchr(char *s, int c)
{
	if (!s)
		return NULL;
	int i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return s+i;
		i++;
	}
	return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	int i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return dest;
}

size_t ft_strlen(char *s)
{
	if (!s)
		return (0);
	size_t ret = 0;
	while (s[ret])
	{
		ret++;
	}
	return (ret);
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char *tmp = malloc(size2 + size1 +1);
	if (!tmp)
		return 0;
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return 1;
}

int str_append_str(char **s1, char *s2)
{
	if (!s2)
		return (1);
	else
		return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
	int i;
	if (!dest || !src)
		return NULL;
	if (dest > src)
	{
		while(n--)
			((char *)dest)[n] = ((char *)src)[n];
	}
	else
	{
		i = 0;
		while (i<n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	// if (dest > src)
	// 	return ft_memcpy(dest, src, n);
	// else if (dest == src)
	// 	return dest;
	// size_t i = ft_strlen((char *)src) - 1;
	// while (i >= 0)
	// {
	// 	((char *)dest)[i] = ((char *)src)[i];
	// }
	return dest;
}

char *get_next_line(int fd)
{
	if (fd<0 || BUFFER_SIZE <= 0)
		return NULL;
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, b))
			return NULL;
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
		{
			free(ret);
			return NULL;
		}
		if (read_ret == 0)
			break;
		b[read_ret] = 0;
		ft_strchr(tmp,'\n');
	}
	if (!tmp)
	{
		if (ret && *ret)
		{
			b[0] = '\0';
			return (ret);
		}
		free(ret);
		return NULL;
	}
	if (!str_append_mem(&ret, b, tmp - b  + 1))
	{
		free(ret);
		return (NULL);
	}
	ft_memmove(b,tmp+1,ft_strlen(tmp + 1)+1);
	return ret;
}

int main()
{
	char *line ;
	int fd = open("dosya.txt",O_RDONLY,0777);
	while ((line = get_next_line(fd))!= NULL)	
	{
		printf("%s",line);
		free(line);
	}
}