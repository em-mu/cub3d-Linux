/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 10:28:57 by emuller           #+#    #+#             */
/*   Updated: 2022/11/07 13:36:45 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*s;
	size_t	i;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	i = 0;
	s = malloc(count * size);
	if (!s)
		return (0);
	while (i < (count * size))
	{
		*(s + i) = 0;
		i++;
	}
	return (s);
}
