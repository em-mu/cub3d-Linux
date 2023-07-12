/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:37:40 by emuller           #+#    #+#             */
/*   Updated: 2022/12/19 15:46:31 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strlcpy2(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] && i < (dstsize - 1) && dstsize > 0)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*ft_strjoin2(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1)
		s1 = ft_calloc(1, 1);
	if (!s2 && s1)
		free(s1);
	if (!s1 || !s2)
		return (0);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
	{
		free(s1);
		return (0);
	}
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	free(s1);
	return (str);
}

int	ft_strchr2(char *s, int c)
{
	int		i;
	char	*str;

	if (!s)
		return (-1);
	str = (char *)s;
	i = 0;
	while (str[i] && str[i] != (unsigned char)c)
		i++;
	if (str[i] == 0 && (unsigned char)c != 0)
		return (0);
	return (1);
}
