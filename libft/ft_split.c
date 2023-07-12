/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:35:34 by emuller           #+#    #+#             */
/*   Updated: 2022/11/07 14:15:10 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strdup_char(char const *src, char c)
{
	char	*copy;
	int		i;

	i = 0;
	while (src[i] && src[i] != c)
		i++;
	copy = malloc((i * sizeof(char) + 1));
	if (copy == 0)
		return (0);
	i = 0;
	while (src[i] && src[i] != c)
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	count_words(char const *str, char c)
{
	int	i;
	int	count;
	int	t;

	if (!str)
		return (-2);
	count = 0;
	i = 0;
	t = 1;
	while (str[i])
	{
		if (str[i] == c)
			t = 1;
		else if (t == 1)
		{
			t = 0;
			count++;
		}
		i++;
	}
	return (count);
}

void	*ft_free_tab(char **tab, int j)
{
	int	k;

	k = 0;
	while (k < j)
	{
		free(tab[k]);
		k++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		j;
	char	**tab;

	tab = malloc(((count_words(str, c) + 1) * sizeof(char *)));
	if (tab == 0)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			tab[j] = ft_strdup_char(str + i, c);
			if (!tab[j])
				return (ft_free_tab(tab, j));
			j++;
		}
		while (str[i] && str[i] != c)
			i++;
	}
	tab[j] = 0;
	return (tab);
}
