/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 12:08:03 by emuller           #+#    #+#             */
/*   Updated: 2022/11/07 14:21:27 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		end;
	int		start;
	char	*str;

	if (!s1)
		return (0);
	start = -1;
	end = ft_strlen(s1) + 1;
	while (s1[++start])
	{
		if (ft_strchr(set, s1[start]) == 0)
			break ;
	}
	while (--end > 0)
	{
		if (ft_strchr(set, s1[end]) == 0)
			break ;
	}
	if (end == 0)
		return (ft_calloc(1, 1));
	str = malloc(end - start + 2);
	if (!str)
		return (0);
	ft_strlcpy(str, (s1 + start), (end - start + 2));
	return (str);
}
