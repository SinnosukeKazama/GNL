/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skazama <skazama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 23:36:40 by skazama           #+#    #+#             */
/*   Updated: 2025/11/02 02:51:49 by skazama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	db_putascii(char *s)
{
	while (*s != '\0')
	{
		printf("%d", *s);
		++s;
	}
}

char	*get_next_line(int fd)
{
	char	*buf1;
	char	*buf2;//char	buf2[BUFFER_SIZE];
	char	*ptrj;
	ssize_t	sz_read;

	buf2 = ft_calloc(GUARD_BS, sizeof(char));
	if (!buf2)
		return (NULL);
	while (1)
	{
		
//buf初期化
		buf1 = ft_calloc(GUARD_BS, sizeof(char));
		if (!buf1)
			return (NULL);
//読み込み
		sz_read = read(fd, buf1, GUARD_BS - 1);
//読み込んだものを出力
printf("In GNL, buf1:%s#\n", buf1);
		if (buf2[0]=='\0')
			ptrj = ft_strjoin(buf2, buf1);
		else
			ptrj = ft_strjoin(ptrj, buf1);
printf("In GNL, ptrj:%s#\n", ptrj);
		if (ft_strchr(buf1, '\n'))
		{
			free(buf1);
			free(buf2);
			return (ptrj);//rignt move. Finely to be return (one_l);
		}
		else if (sz_read <= 0 || !ptrj)
		{
			free(buf1);
			free(buf2);
			return (NULL);//error or EOF.
		}
//読み込んだものを一時保存
		ft_strcpy(buf2, buf1);
	}
}
/*
THE FLOW OF THE FUNCTION.
1)ファイルを一行だけ読み込む。

2)読み込んだ文字列用のメモリ確保。

3)読み込んだ文字列をバッファにコピー。

E)バッファを返す。

*/
int	main(void)
{
	int	fd;
	
	if (BUFFER_SIZE / sizeof(char) > SIZE_MAX)
	{
		printf("ERROR:Too many BUFFER_SIZE\n");
		return (1);
	}
	fd = open("testGNL.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Failed to open file.\n");
		return (1);
	}
	char	*onel;

	onel = get_next_line(fd);
	printf("onel:%s#\n", onel);

	close(fd);
	return (0);
}
