#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 16
#endif//BUFFFER_SIZE
typedef struct	s_line{
	int	fd;
	char *s;
	unsigned int i;
}	t_line;



//ファイルから一文字読み取り、それを返す関数。
int	getf(int fd)
{
	int	c;

	c = 0;
	ssize_t szr = 0;
	if (fd <= 0)//fd error
		return (-2);
	szr = read(fd, &c, 1);
	if (szr < 0)
		return (-2);
	if (szr == EOF)
		return (0);
printf("In getf, szr:%zu#\n", szr);
	return (c);
}

//
char *gnl(int fd)
{
	t_line	*s;
	int c;

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
		c = getf(fd);
		if (c == -2)
		{
			free(s->s);
			return (free(s), NULL);
		}
		s->s[s->i] = (char)c;
printf("In gnl, c:%d#\n", c);
printf("In gnl, s->s[%d]:%c#\n", s->i, s->s[s->i]);
		if (c == '\n')
			return (s->s[++s->i] = '\0', s->s);
		if (c == EOF)
			return (s->s[s->i], s->s);
		if ((s->i % (BUFFER_SIZE - 1)) == 0)
		{
			s->s = realloc(s->s, BUFFER_SIZE + s->i);//you ganna make it.
			if (!s->s)
				return (free(s), NULL);
		}
		++(s->i);
		//if(s->i == 16)break;//DBG
	}
	return (s->s);
}

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	printf("In main,opened.\n");
	char *s1 = gnl(fd);
	char *s2 = gnl(fd);
	printf("In main#%s#\n", s1);
	printf("In main#%s#\n", s2);

	close(fd);
	return (0);
}
