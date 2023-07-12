/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:54:17 by emuller           #+#    #+#             */
/*   Updated: 2022/12/16 09:55:15 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(long int n, char a, int len, int tmp)
{
	if (n < 0)
	{
		len += write(1, "-", 1);
		if (len == -1)
			return (-1);
		n = -n;
	}
	if (n > 9)
	{
		tmp = ft_putnbr(n / 10, 0, 0, 0);
		if (tmp == -1)
			return (-1);
		len += tmp;
	}
	a = n % 10 + '0';
	tmp = 0;
	tmp = write(1, &a, 1);
	if (tmp == -1)
		return (-1);
	len += tmp;
	return (len);
}

int	ft_unsigned_putnbr(unsigned int i, char a, int len, int tmp)
{
	if (i > 9)
	{
		tmp = ft_unsigned_putnbr(i / 10, 0, 0, 0);
		if (tmp == -1)
			return (-1);
		len += tmp;
	}
	a = i % 10 + '0';
	tmp = 0;
	tmp = write(1, &a, 1);
	if (tmp == -1)
		return (-1);
	len += tmp;
	return (len);
}

int	ft_putnbr_hex(unsigned int i, int maj, int len, int tmp)
{
	int		a;
	char	*b;

	a = i % 16;
	if (maj == 0)
		b = "0123456789abcdef";
	else
		b = "0123456789ABCDEF";
	if (i >= 16)
	{
		tmp = ft_putnbr_hex(i / 16, maj, 0, 0);
		if (tmp == -1)
			return (-1);
		len += tmp;
		a = i % 16;
		i = i / 16;
	}
	tmp = 0;
	tmp = write(1, &b[a], 1);
	if (tmp == -1)
		return (-1);
	len += tmp;
	return (len);
}

int	ft_putnbr_lhex(unsigned long long int i, int maj, int len, int tmp)
{
	unsigned long long int	a;
	char					*b;

	a = i % 16;
	if (maj == 0)
		b = "0123456789abcdef";
	else
		b = "0123456789ABCDEF";
	if (i >= 16)
	{
		tmp = ft_putnbr_lhex(i / 16, maj, 0, 0);
		if (tmp == -1)
			return (-1);
		len += tmp;
		a = i % 16;
		i = i / 16;
	}
	tmp = 0;
	tmp = write(1, &b[a], 1);
	if (tmp == -1)
		return (-1);
	len += tmp;
	return (len);
}
