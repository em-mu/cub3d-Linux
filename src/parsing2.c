/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:59:55 by emuller           #+#    #+#             */
/*   Updated: 2023/08/02 17:33:46 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	read_texture_data(char **file)
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
	check_tex_num(file_tex_only);
	fill_tex_data(&tex, file_tex_only);
	free_tab(file_tex_only);
	return (tex);
}

void	check_tex_num(char **file)
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
		exit(1);
	}
}

void	fill_color(int *tex, char **str)
{
	char	**rgb;
	int		i;

	rgb = ft_split(str[1], ',');
	i = 0;
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
			exit(1);
		}
		free_tab(tmp);
		tmp = NULL;
	}
}
