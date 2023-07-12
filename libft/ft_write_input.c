/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:16:43 by emuller           #+#    #+#             */
/*   Updated: 2022/12/16 09:55:31 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_write_char(va_list ap)
{
	unsigned char	c;

	c = va_arg(ap, int);
	return (write(1, &c, 1));
}

int	ft_write_str(va_list ap)
{
	char	*s;

	s = va_arg(ap, char *);
	if (!s)
	{
		return (write(1, "(null)", 6));
	}
	return (write(1, s, ft_strlen(s)));
}

int	ft_write_int(va_list ap, int is_unsigned)
{
	int				len;
	long int		i;
	unsigned int	j;

	len = 0;
	if (is_unsigned == 0)
	{
		i = va_arg(ap, int);
		len = ft_putnbr(i, 0, 0, 0);
	}
	else if (is_unsigned == 1)
	{
		j = va_arg(ap, unsigned int);
		len = ft_unsigned_putnbr(j, 0, 0, 0);
	}
	return (len);
}

int	ft_write_hex(va_list ap, int maj)
{
	unsigned int	n;
	int				len;

	len = 0;
	n = va_arg(ap, unsigned int);
	len = ft_putnbr_hex(n, maj, 0, 0);
	return (len);
}

int	ft_write_pointer_adress(va_list ap)
{
	unsigned long long int	s;
	int						len;

	len = 0;
	s = va_arg(ap, unsigned long long int);
	len = write(1, "0x", 2);
	if (len == -1)
		return (len);
	len += ft_putnbr_lhex(s, 0, 0, 0);
	if (len == 1)
		return (-1);
	return (len);
}
