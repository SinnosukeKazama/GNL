#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 16
#endif//BUFFFER_SIZE

typedef struct s_buf{
	char bf[BUFFER_SIZE];
	int	fd;
	ssize_t sz_read;
}	t_buf;
//文字配列取得関数
t_buf	*fgetbf(t_buf *b, const int fd)
{
	if (fd < 0)//fd error
		return (NULL);
	b->fd = fd;
	b->sz_read = read(b->fd, b->bf, BUFFER_SIZE);
printf("In getf, fd:%d, bf:%s, szr:%zu#\n",b->fd, b->bf, b->sz_read);
	if (b->sz_read <= 0)//end of file
		return (NULL);
	return (b);
}

//文字配列走査関数
bool	isc_in(const t_buf b, const char c)
{
	size_t	i;

	i = 0;
	while (i < b.sz_read)
	{
		if (b.bf[i] == c)
			return (true);
		++i;
	}
	return (false);
}

char	*gnl(int fd)
{
	static t_buf	*b;
	b = fgetbf(b, (const int)fd);
	if (!b)
		return(NULL);
	printf("bf:%s\n", b->bf);
	bool isendl = isc_in((const t_buf)*b, '\n');
	printf("isendl:%d\n", isendl);
	return (NULL);
}

int main(void)
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	printf("Inmain, fd:%d\n",fd);
	if (fd < 0)
		return (1);
	gnl(fd);
	close(fd);
	return (0);
}
