/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:52:52 by emuller           #+#    #+#             */
/*   Updated: 2023/08/02 17:07:22 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_format(char *s)
{
	int	i;
	int	fd;

	fd = open(s, O_DIRECTORY);
	if (fd != -1)
	{
		printf("Error \nInvalid map : is a directory\n");
		close(fd);
		return (-1);
	}
	if (ft_strchr(s, '/') != 0)
		s = ft_strrchr(s, '/');
	i = ft_strlen(s) - 1;
	if (i <= 3)
	{
		printf("Error \nInvalid map name\n");
		return (-1);
	}
	if (s[i] != 'b' || s[--i] != 'u' || s[--i] != 'c' || s[--i] != '.')
	{
		printf("Error \nInvalid map format : .cub\n");
		return (-1);
	}
	return (0);
}

int	check_valid_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == 0 || str[i] != '1' || (str[ft_strlen(str) - 1] != '1'
			&& str[ft_strlen(str) - 1] != ' '))
		return (-1);
	i = 0;
	while (str[i])
	{
		if (!is_valid_char(str[i]))
		{
			printf("Error\nInvalid map: Unknown character\n");
			exit(1);
		}
		i++;
	}
	return (0);
}

void	check_closed_map(int i, char **map)
{
	int	j;

	j = 0;
	while (map[i][j] && (map[i][j] == '1' || map[i][j] == ' '
			|| map[i][j] == '\t'))
		j++;
	if (map[i][j])
		exit_error(map, "Invalid map: map not closed");
	while (map[i] && i < find_end_map(map))
	{
		if (check_valid_line(map[i]) == -1)
			exit_error(map, "Invalid map: map not closed");
		i++;
	}
	i--;
	j = 0;
	while (map[i][j] && (map[i][j] == '1' || map[i][j] == ' '
			|| map[i][j] == '\t'))
		j++;
	if (map[i][j])
		exit_error(map, "Invalid map: map not closed");
}

int	check_around(char **map, int i, size_t j)
{
	if (map[i][j - 1] && map[i][j - 1] != '1' && map[i][j - 1] != ' '
		&& map[i][j - 1] != '\n')
		return (-1);
	else if (map[i][j + 1] && map[i][j + 1] != '1' && map[i][j + 1] != ' '
			&& map[i][j + 1] != '\n')
		return (-1);
	else if (map[i + 1] && j <= ft_strlen(map[i + 1]) && map[i + 1][j] != '1'
			&& map[i + 1][j] != ' ' && map[i + 1][j] != '\n')
		return (-1);
	else if (i > 1 && map[i - 1] && j <= ft_strlen(map[i - 1]) && map[i
			- 1][j] != '1' && map[i - 1][j] != ' ' && map[i - 1][j] != '\n')
		return (-1);
	return (0);
}
