#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 128
ssize_t sizeoffile(int fd)
{
	ssize_t	sz_read = 0;
	ssize_t	sum = 0;
	char buf[BUFFER_SIZE];

	while ((sz_read = read(fd, buf, sizeof(buf))) > 0)
		sum += sz_read;
	return (sum);
}

ssize_t sizeofendl(int fd)
{
	ssize_t	sz_read = 0;
	ssize_t	sum = 0;
	char buf[1];

	while ((sz_read = read(fd, buf, sizeof(buf))) > 0)
	{
		sum += sz_read;
		if (buf[0] == '\n')
			break;
	}

//printf("#buf:%s\n", buf);
	return (sum);
}

/*
RT > 0 :index of c.
RT = 0 :not find.
*/
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

int main(void)
{
	const int fd = open("test_sizeoffile.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR:open\n");
		return (1);
	}
	//printf("size of the file(%zu)\n", sizeoffile(fd));
	printf("size of the endl(%zu)\n", sizeofendl(fd));//1行目 ok
	printf("size of the endl(%zu)\n", sizeofendl(fd));//2行目 ok
	printf("size of the endl(%zu)\n", sizeofendl(fd));//3行目
	close(fd);
	return (0);
}
/*
//返り値にc 含まず。
size_t	strlento(char c, char *s)
{
	unsigned int	i = 0;

	while (s[i] != '\0' && s[i] != '\n')
		++i;
	return (i);
}
問題点：複数回呼び出せない。なぜならバッファサイズ分だけ読み込むから。
ssize_t sizeofendl(int fd)
{
	ssize_t	sz_read = 0;
	ssize_t	sum = 0;
	char buf[BUFFER_SIZE];

	while ((sz_read = read(fd, buf, sizeof(buf)-1)) > 0)
	{
		buf[sz_read] = '\0';
		if (strlen(buf) == strlento('\n', buf))
			sum += sz_read;
		else if (strlen(buf) > strlento('\n', buf))
			sum += (ssize_t)(strlento('\n', buf) * sizeof(char));
	}
//printf("#buf:%s\n", buf);
	return (sum);
}
*/
