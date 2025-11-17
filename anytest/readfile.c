#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 128

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
