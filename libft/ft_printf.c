/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:23:34 by emuller           #+#    #+#             */
/*   Updated: 2022/12/16 09:56:34 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_findtype(va_list ap, char a)
{
	int	len;

	len = 0;
	if (a == 'c')
		len = ft_write_char(ap);
	else if (a == 's')
		len = ft_write_str(ap);
	else if (a == 'i' || a == 'd')
		len = ft_write_int(ap, 0);
	else if (a == 'u')
		len = ft_write_int(ap, 1);
	else if (a == 'x')
		len = ft_write_hex(ap, 0);
	else if (a == 'X')
		len = ft_write_hex(ap, 1);
	else if (a == 'p')
		len = ft_write_pointer_adress(ap);
	else if (a == '%')
		len = write(1, &a, 1);
	else
		len = write(1, &a, 1);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		len;
	int		tmp;

	tmp = 0;
	len = 0;
	i = -1;
	va_start(ap, str);
	while (str[++i])
	{
		if (str[i] == '%')
			tmp = ft_findtype(ap, str[++i]);
		else
			tmp = write(1, &str[i], 1);
		len += tmp;
		if (tmp == -1)
			return (len);
	}
	va_end(ap);
	return (len);
}
