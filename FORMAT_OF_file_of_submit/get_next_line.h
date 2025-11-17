/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skazama <skazama@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 23:41:00 by skazama           #+#    #+#             */
/*   Updated: 2025/11/02 02:40:01 by skazama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#include <fcntl.h>//O_RDONLY
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>//Debug###########################

char	*ft_strchr(const char *s, int c);
void	init_buf(char	*buf);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcpy(char *dest, char *src);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);

#ifndef MAX
# define MAX(x,y) ((x)>(y)?(x):(y))
#endif//MAX
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif//BUFFER_SIZE
#ifndef GUARD_BS
# define GUARD_BS MAX(BUFFER_SIZE, 2)
#endif//GUARD_BS


#endif//GET_NEXT_LINE_H
