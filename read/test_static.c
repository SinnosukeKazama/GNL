#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>//printf
#include <string.h>//strcpy
#include <stdint.h>
#include <stdlib.h>
#define BUFFER_SIZE 128
/*

size_t	strlento(char c, char *s)
{
	size_t	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		++i;
	}
	return (i);
}
char	*gnl(const int fd)
{
	ssize_t	sz_read = 0;
	ssize_t	sum = 0;
	char	*buf_0;
	char	buf_t[BUFFER_SIZE];
	size_t	ltc = 0;//lenge to the char

	buf_00 = NULL;
	while ((sz_read = read(fd, buf_t, sizeof(buf_t) - 1)) > 0)
	{
		ltc = strlento('\n', buf_t);
		buf_0 = ft_substr(buf_t, 0, ltc);
		buf_00 = ft_strjoin(buf_0, );//may be leak!!!
		free (buf_0);
		if (ltc != strlen(buf_t))//Find c in buf_t
			break ;
	}
	return (buf_00);
}
*/
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr_s;
	unsigned int	i;

	ptr_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr_s[i] = c;
		++i;
	}
	return (s);
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	size_allocate;

	size_allocate = size * nmemb;
	if (size_allocate == 0)
		size_allocate = 1;
	else if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(size_allocate);
	if (!ptr)
		return (NULL);
	ptr = ft_memset(ptr, 0, size_allocate);
	return (ptr);
}
void	bufcpy(char *buf, ssize_t szread)
{
	static char	*buf_al = ft_calloc(BUFFER_SIZE, sizeof(char));
	static ssize_t	szsum = 0;
	if (!buf_al)
		return ;
	szsum += szread;
	strcpy(&buf_al[szsum], buf);
	printf("In bufcpy, buf_al:%s#\n", buf_al);
}
int	tstatic(const int  fd)
{
	char buf_t[3];
	ssize_t	szread;

	while ((szread = read(fd, buf_t, sizeof(buf_t) - 1)) > 0)
	{
		buf_t[szread] = '\0';
		bufcpy(buf_t, szread);
		printf("##%s#\n", buf_t);
	}
}

int main(void)
{
	const int fd = open("test_sizeoffile.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR:open\n");
		return (1);
	}

	tstatic(fd);

	close(fd);
	return (0);
}

