/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:41:32 by emuller           #+#    #+#             */
/*   Updated: 2022/12/13 16:59:53 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	i;
	int	size;

	i = 0;
	if (!lst)
		return (NULL);
	size = ft_lstsize(lst);
	while (i < (size - 1))
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
