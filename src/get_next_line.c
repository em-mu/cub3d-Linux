/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:35:49 by emuller           #+#    #+#             */
/*   Updated: 2022/12/19 11:55:56 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_init(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
	return (0);
}

char	*ft_read_save(int fd, char *tmp)
{
	ssize_t	size;
	char	*buf;

	size = 1;
	if (!tmp)
		tmp = ft_calloc(1, 1);
	if (!tmp)
		return (0);
	while (size > 0 && ft_strchr2(tmp, '\n') == 0)
	{
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
			return (ft_free_init(&tmp));
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1)
		{
			free(buf);
			return (0);
		}
		tmp = ft_strjoin2(tmp, buf);
		free(buf);
	}
	return (tmp);
}

char	*ft_get_line(char *tmp)
{
	size_t	i;
	size_t	len;
	char	*result;

	i = 0;
	if (!tmp)
		return (0);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == 0)
		len = i + 1;
	else
		len = i + 2;
	result = ft_calloc(len, sizeof(char));
	if (!result)
		return (0);
	ft_strlcpy2(result, tmp, len);
	return (result);
}

char	*ft_after_nl(char *tmp)
{
	size_t	i;
	size_t	j;
	char	*new_tmp;

	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == 0)
		return (ft_free_init(&tmp));
	if (tmp[i] == '\n')
		i++;
	new_tmp = ft_calloc((ft_strlen(tmp) - i + 1), sizeof(char));
	if (!new_tmp)
		return (ft_free_init(&tmp));
	j = 0;
	while (tmp[i])
		new_tmp[j++] = tmp[i++];
	free(tmp);
	tmp = NULL;
	return (new_tmp);
}

char	*get_next_line(int fd)
{
	char		*result;
	static char	*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &result, 0) < 0)
		return (ft_free_init(&tmp));
	tmp = ft_read_save(fd, tmp);
	if (!tmp || tmp[0] == 0)
	{
		if (tmp)
			free(tmp);
		tmp = NULL;
		return (0);
	}
	result = ft_get_line(tmp);
	if (!result)
		return (ft_free_init(&tmp));
	tmp = ft_after_nl(tmp);
	return (result);
}
