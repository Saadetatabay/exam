#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
	int i = 0;
	while (s[i] != c && s[i])
		i++;
	if (s[i] == c)
		return s + i;
	else
		return NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t  i;
    i = 0;
	while (i < n)
    {
		((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
	return dest;
}

size_t ft_strlen(char *s)
{
	size_t ret = 0;
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1;
    if (!*s1)
        size1 = 0;
    else
	    size1 = ft_strlen(*s1);

	char *tmp = malloc(size2 + size1 +1);
	if (!tmp)
		return 0;
    if (*s1)
	    ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return 1;
}

int str_append_str(char **s1, char *s2)
{
    if (s2)
	    return str_append_mem(s1, s2, ft_strlen(s2));
    else
        return 1;
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
    if (dest == src || n == 0)
        return dest;
	else if (dest < src)
        return ft_memcpy(dest, src, n);
	//size_t i = ft_strlen((char *)src) - 1;
	while (n-- > 0)
	{
		((char *)dest)[n] = ((char *)src)[n];
    }
	return dest;
}

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = "";
	char *ret = NULL;
	char *tmp = ft_strchr(b, '\n'); // new line kısmı
	while (!tmp)
	{
        perror("s1");
		if (!str_append_str(&ret, b))
			return NULL;
		int read_ret = read(fd, b, BUFFER_SIZE); // b ye okuma yaptık
		perror("s2");
        if (read_ret == -1)
			return NULL;
        if (read_ret == 0)
            break;
		b[read_ret] = 0;
        tmp = ft_strchr(b, '\n'); // eğer b içinde new line varsa
	}
    if (!tmp) //byte ret == 0 ise
    {
        if (ret && *ret)  // ret'te veri var mı?
        {
            b[0] = '\0';  // Buffer'ı temizle
            return ret;
        }
        free(ret);  // Boş ret'i temizle
        return NULL;
    }
    //buraya tempde newline olmayan kısmı rete ekliyoruz
	if (!str_append_mem(&ret, b, tmp - b  + 1))
	{
		free(ret);
		return (NULL);
	}
    ft_memmove(b,tmp + 1,ft_strlen(tmp + 1) + 1);

	return ret;
}

#include <stdio.h>

int main(void)
{
	int fd;
	char *line;

	fd = open("text.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Dosya açılamadı");
		return (1);
	}
	//perror("dosyaacıldi");
	while ((line = get_next_line(fd)) != NULL)
	{
		//perror("line");
		printf("satır: %s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}