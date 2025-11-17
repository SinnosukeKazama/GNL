#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 16
#endif//BUFFFER_SIZE
#define FGET_ERROR -2
#define FGET_EOF -1
typedef struct	s_line{
	int	fd;
	char *s;
	unsigned int i;
}	t_line;

/*
static void	*ft_calloc(size_t nmemb, size_t size)
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
}*/
//ファイルから一文字読み取り、それを返す関数。
/*
fget
RETURN:
error..-2
succssed..0~255
EOF..-1
*/
int	fget(int fd)
{
	unsigned char	c;
	ssize_t szr;

	if (fd < 0)//fd error
		return (FGET_ERROR);
	szr = read(fd, &c, 1);
	if (szr < 0)
		return (FGET_ERROR);
	if (szr == 0)//end of file.
		return (FGET_EOF);
	return (c);
}

char *gnl(int fd)
{
	t_line	*s;
	char	*tmp;
	int	c;

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > SIZE_MAX)
		return (NULL);
	s = malloc(sizeof(t_line));
	if (!s)
		return (NULL);
	s->fd = fd;
	s->i = 0;
	s->s = malloc(BUFFER_SIZE);
	if (!s->s)
		return (free(s), NULL);
	while (1)
	{
		c = fget(fd);
//printf("In gnl, c:%d#\n", c);
//printf("In gnl, s->s[%d]:%c#\n", s->i, s->s[s->i]);
		if (c == FGET_ERROR)
			return (free(s->s), free(s), NULL);
		else if (c == FGET_EOF)
		{
			if (s->i == 0)
				return (free(s->s), free(s), NULL);
			s->s[s->i] = '\0';//X
			tmp = s->s;//X
			return (free(s), tmp);
		}
		s->s[(s->i)++] = (char)c;
		if (c == '\n')
		{
			s->s[s->i] = '\0';//X
			tmp = s->s;//X
			return (free(s), tmp);
		}
		if (s->i > 0 && s->i % BUFFER_SIZE == 0)
		{
			tmp = realloc(s->s, BUFFER_SIZE + s->i);//you ganna make it.
			if (!tmp)
				return (free(s->s), free(s), NULL);
			s->s = tmp;
		}
	}
}

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	printf("In main,opened.\n");
	char *s1;

	while ((s1 = gnl(fd)) != NULL)
	{
		printf("In main#%s#\n", s1);
		free(s1);
	}
	
	close(fd);
	return (0);
}
/*
tips:
EOF..-1 or the system dependence.
*/
