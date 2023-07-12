/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:51:58 by emuller           #+#    #+#             */
/*   Updated: 2022/11/06 21:19:27 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_size(long int n)
{
	int	size;

	size = 0;
	if (n <= 0)
	{
		n = -n;
		size++;
	}
	while (n > 0)
	{
		size++;
		n /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char		*tab;
	int			size;
	long int	ln;

	ln = (long int)n;
	size = count_size(ln);
	tab = malloc((size + 1) * sizeof(char));
	if (!tab)
		return (0);
	if (ln < 0)
	{
		tab[0] = '-';
		ln = -ln;
	}
	tab[size] = 0;
	size--;
	if (ln == 0)
		tab[0] = '0';
	while (ln > 0)
	{
		tab[size] = ln % 10 + '0';
		ln /= 10;
		size--;
	}
	return (tab);
}
