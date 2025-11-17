/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skazama <skazama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 23:38:43 by skazama           #+#    #+#             */
/*   Updated: 2025/11/02 01:18:10 by skazama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//g_n_l の補助関数を追加するファイル。
char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr_s;

	i = -1;
	ptr_s = (char *)s;
	while (ptr_s[++i] != '\0')
		if (ptr_s[i] == (char)c)
			return (&ptr_s[i]);
	return (NULL);
}

void	init_buf(char	*buf)
{
	unsigned int	i;

	i = 0;
	while (i < BUFFER_SIZE)
		buf[i++] = '\0';
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*jointed_s;
	const size_t	len_s1 = ft_strlen(s1);
	const size_t	len_s2 = ft_strlen(s2);
	const size_t	num_allocate = len_s1 + len_s2 + 1;

	jointed_s = (char *)ft_calloc(num_allocate, sizeof(char));
	if (jointed_s)
	{
		ft_strlcpy(jointed_s, s1, len_s1 + 1);
		ft_strlcpy(&jointed_s[len_s1], s2, len_s2 + 1);
		return (jointed_s);
	}
	return (NULL);
}
char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return (dest);
}
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		dest[i] = '\0';
	}
	else
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			++i;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src) * sizeof(char));
}
size_t	ft_strlen(const char *s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
		;
	return (i);
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	size_allocate;

	size_allocate = size * nmemb;
	if (size_allocate == 0 || nmemb > SIZE_MAX / size)
		size_allocate = 1;
	ptr = malloc(size_allocate);
	if (!ptr)
		return (NULL);
	ptr = ft_memset(ptr, 0, size_allocate);
	return (ptr);
}
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
