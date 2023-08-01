/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <charlesbrunet51220@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:59:55 by emuller           #+#    #+#             */
/*   Updated: 2023/06/27 17:18:01 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_len_max(char **map, int len, int k)
{
	int line_length;
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
	while(i < 8)
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
	int i;
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

t_texture	read_texture_data(char	**file)
{
	t_texture	tex;
	char		**file_tex_only;
	int			i;

	i = 0;
	while (file[i] && find_beginning_map(file[i]) == 0)
		i++;
	file_tex_only = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (file[++i] && find_beginning_map(file[i]) == 0)
		file_tex_only[i] = ft_strdup(file[i]);
	check_tex_num(file_tex_only); // il faut free les 2 char ** quand on exit
	fill_tex_data(&tex, file_tex_only); // il faut free les 2 char ** quand on exit
	free_tab(file_tex_only);
	return (tex);
}

void	check_tex_num(char 	**file)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (file[++i])
	{
		if (line_empty(file[i]))
			continue ;
		count++;
	}
	if (count != 6)
	{
		printf("Error \nInvalid texture: wrong number of textures\n");
		exit (1);
	}
}

void	fill_color(int *tex, char **str)
{
	char **rgb;

	rgb = ft_split(str[1], ',');
	int i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
	{
		printf("Error \nInvalid texture: wrong identifier\n");
		free_tab(str);
		free_tab(rgb);
		exit(-1);
	}
	i = -1;
	while (rgb[++i])
		tex[i] = ft_atoi(rgb[i]);
	free_tab(rgb);
}

void	fill_tex_data(t_texture *tex, char **file)
{
	char	**tmp;
	int		i;

	i = -1;
	while (file[++i])
	{
		if (line_empty(file[i]))
			continue ;
		tmp = ft_split(file[i], ' ');
		if (!ft_strncmp(tmp[0], "NO", 2) && !tmp[0][2] && !tmp[2])
			tex->north = ft_strdup(tmp[1]);
		else if (!ft_strncmp(tmp[0], "SO", 2) && !tmp[0][2] && !tmp[2])
			tex->south = ft_strdup(tmp[1]);
		else if (!ft_strncmp(tmp[0], "WE", 2) && !tmp[0][2] && !tmp[2])
			tex->west = ft_strdup(tmp[1]);
		else if (!ft_strncmp(tmp[0], "EA", 2) && !tmp[0][2] && !tmp[2])
			tex->east = ft_strdup(tmp[1]);
		else if (!ft_strncmp(tmp[0], "F", 1) && !tmp[0][1] && !tmp[2])
			fill_color(tex->floor, tmp);
		else if (!ft_strncmp(tmp[0], "C", 1) && !tmp[0][1] && !tmp[2])
			fill_color(tex->ceiling, tmp); 
		else
		{
			printf("Error \nInvalid texture: wrong identifier\n");
			free_tab(tmp);
			exit (1);
		}
		free_tab(tmp);
		tmp = NULL;
	}
}
