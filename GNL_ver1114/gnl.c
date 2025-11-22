#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 64
#endif//BUFFFER_SIZE
#define FGS_ERROR -2
#define FGS_EOF 0
#define EOL '\n'

//file of get_next_line_utils.c--------------------------
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		++i;
	return (i);
}

size_t	strlen_toc(const char *s, const char c, const size_t index_start)
{
	size_t	i;
	size_t	len;

	if (index_start > ft_strlen(s) - 1)//error
		return (0);
	if (!s)
		return (0);
	i = index_start;
	len = 0;
	while (s[i] != '\0')
	{
		++len;
		if (s[i] == c)
			break;
		++i;
	}
	return (len);
}

bool	isc_ins(const char *s, const char c, const size_t index_start)
{
	size_t	i;

	if (index_start > ft_strlen(s) - 1)//error
		return (0);
	i = index_start;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (true);
		++i;
	}
	return (false);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			++i;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	const size_t	element_n = ft_strlen(s) + 1;
	char			*dest;

	if (!s)
		return (malloc(sizeof(char)));
	dest = (char *)malloc(element_n * sizeof(char));
	if (dest)
	{
		ft_strlcpy(dest, s, element_n);
		dest[ft_strlen(s)] = '\0';
		return (dest);
	}
	return (NULL);
}
char	*ft_substr(const char const *s, unsigned int start, size_t len)
{
	char			*subs;
	unsigned int	i;

	i = 0;
	if (!s)
		return (malloc(sizeof(char)));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start > ft_strlen(s) - 1)
		start = ft_strlen(s);
	while (s[start + i] != '\0' && i < len)
		++i;
	subs = (char *)malloc((i + 1) * sizeof(char));
	if (subs)
	{
		ft_strlcpy(subs, &s[start], i + 1);
		subs[len] = '\0';
		return (subs);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*jointed_s;
	const size_t	len_s1 = ft_strlen(s1);
	const size_t	len_s2 = ft_strlen(s2);
	const size_t	num_allocate = len_s1 + len_s2 + 1;

	if (!s1 && !s2)
		return (malloc(sizeof(char)));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	jointed_s = (char *)malloc(num_allocate * sizeof(char));
	if (jointed_s)
	{
		ft_strlcpy(jointed_s, s1, len_s1 + 1);
		ft_strlcpy(&jointed_s[len_s1], s2, len_s2 + 1);
		jointed_s[len_s1 + len_s2] = '\0';
		return (jointed_s);
	}
	return (NULL);
}
//file of get_next_line.c (unique func)---------------------------
/*
ファイル読み取り関数
fgetstr
RETURN:
error..-2
succssed..sz_read
EOF..0
*/
ssize_t	fgetstr(const int fd, char *buf)
{
	ssize_t sz_read;

	if (fd < 0)//fd error
		return (FGS_ERROR);
	sz_read = read(fd, buf, BUFFER_SIZE);
	if (sz_read == -1)//read error.
		return (FGS_ERROR);
	else if (sz_read == 0)//end of file
		return (FGS_EOF);
	buf[sz_read] = '\0';
	return (sz_read);
}

char	*gnl(int fd)
{
	static char	*buf_sum;	//The elements of "buf_sum" is all element of the file.
	char		*buf_tmp;	//"buf_tmp" is tmp of "buf_sum", when reallocate "buf_sum".
	char		*buf_one;	//"buf_one" Gets string from the file.this buf size is "BUFFER_SIZE".
	char		*buf_eol;	//"buf_eol" is Current index to next EOL in the group of "buf_sum".
	ssize_t		sz_read;	//"sz_read" is Read size at the current loop.
	static size_t	i;		//Current index
	size_t	len_eol;		//"len_eol" is lenge of EOL from current index in the group of "buf_sum".

	if (!buf_sum)
		buf_sum = ft_strdup("");
	buf_one = malloc(BUFFER_SIZE + 1);//one allocate.
	if (!buf_one)
		return (NULL);
	sz_read = 0;
	len_eol = 0;

	while (1)
	{
		if (isc_ins(buf_sum, EOL, i))
		{
			len_eol = strlen_toc(buf_sum, EOL, i);
			buf_eol = ft_substr(buf_sum, i, len_eol);
			i += len_eol;
			return (free(buf_one), buf_eol);
		}
		sz_read = fgetstr((const int)fd, buf_one);
		if (sz_read == FGS_ERROR)
			return (free(buf_one), NULL);
		else if (sz_read == FGS_EOF)
		{
			if (buf_sum[i] != '\0')
			{
				buf_eol = ft_substr(buf_sum, i, ft_strlen(buf_sum) - i);
				i = ft_strlen(buf_one);
				return (free(buf_one), buf_eol);
			}
			return (free(buf_one), NULL);
		}
		else
		{
			buf_tmp = buf_sum;
			buf_sum = ft_strjoin(buf_tmp, buf_one);//sum allocate.
			free(buf_tmp);
		}
	}
}

////////////////////////////////////////////////////////////////////////
int main(void)
{
	int fd = open("./gnl.c", O_RDONLY);
	if (fd == -1)
		return (1);
	printf("In main,opened. fd:%d#\n", fd);
	char *s0;

/*
問題点：最後の行が返ってこない。->FIXED.
	BUFFER_SIZE=1にしたとき、最後にヌルが返ってこない。->ok
*/
	while ((s0 = gnl(fd)) != NULL)
	{
		printf("%s", s0);
		free(s0);
	}

	close(fd);
	return (0);
}
