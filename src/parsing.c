/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:59:55 by emuller           #+#    #+#             */
/*   Updated: 2023/08/02 17:24:28 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_len_max(char **map, int len, int k)
{
	int	line_length;
	int	tmp;

	tmp = 0;
	line_length = ft_strlen(map[0]);
	while (k < len)
	{
		tmp = ft_strlen(map[k]);
		if (tmp > line_length)
			line_length = tmp;
		k++;
	}
	return (line_length);
}

char	*ft_strdup_new(char *s1, int len)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	s = ft_calloc(sizeof(char), len + 1);
	if (!s)
		return (0);
	while (i < 8)
		s[i++] = '1';
	j = 0;
	while (s1[j])
		s[i++] = s1[j++];
	if (ft_strchr(s1, '\n'))
		s[--i] = '1';
	while (i < len)
		s[i++] = '1';
	return (s);
}

void	fill_spaces(char ***map)
{
	int	i;
	int	j;

	i = 0;
	while ((*map)[i])
	{
		j = 0;
		while ((*map)[i][j])
		{
			if ((*map)[i][j] == ' ')
				(*map)[i][j] = '1';
			j++;
		}
		i++;
	}
}

char	**extract_map_from_file(char **map_full_file)
{
	char	**map;
	int		i;
	int		j;
	int		len_map;
	int		len_line;

	i = 0;
	while (map_full_file[i] && !find_beginning_map(map_full_file[i]))
		i++;
	len_map = find_map_len(i, map_full_file);
	check_closed_map(i, map_full_file);
	j = 0;
	map = ft_calloc(sizeof(char *), len_map + 17);
	len_line = get_len_max(map_full_file, len_map, i);
	while (j < 8)
		map[j++] = ft_strdup_new("", len_line + 16);
	while (map_full_file[i] && line_empty(map_full_file[i]) != 1)
	{
		map[j] = ft_strdup_new(map_full_file[i], len_line + 16);
		i++;
		j++;
	}
	i = 0;
	while (i++ < 8)
		map[j++] = ft_strdup_new("", len_line + 16);
	if (check_closed_around_space(map))
	{
		free_tab(map);
		free_tab(map_full_file);
		exit(1);
	}
	fill_spaces(&map);
	return (map);
}
