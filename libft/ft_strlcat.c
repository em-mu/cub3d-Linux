/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:07:15 by emuller           #+#    #+#             */
/*   Updated: 2022/11/07 14:16:13 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t sizedst)
{
	size_t	i;
	size_t	j;
	size_t	len;

	if ((!dst || !src) && sizedst == 0)
		return (0);
	if (ft_strlen(dst) > sizedst)
		len = ft_strlen(src) + sizedst;
	else
		len = ft_strlen(src) + ft_strlen(dst);
	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j] && i < (sizedst - 1) && sizedst > 0)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (len);
}
