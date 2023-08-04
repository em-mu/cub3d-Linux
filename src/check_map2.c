/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:47:33 by emuller           #+#    #+#             */
/*   Updated: 2023/08/02 17:53:23 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_closed_around_space(char **map)
{
	int		i;
	int		count;
	size_t	j;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 1;
		while (map[i][j] && map[i][j + 1])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W'
				|| map[i][j] == 'S')
				count++;
			if (map[i][j] == ' ')
				if (check_around(map, i, j) == -1)
					return (printf("Error \nInvalid map: map not closed\n"));
			j++;
		}
		i++;
	}
	if (count == 0 || count > 1)
		return (printf("Error \nInvalid map: wrong player number\n"));
	return (0);
}

void	load_tex(t_game *game)
{
	game->north = mlx_load_png(game->tex.north);
	game->south = mlx_load_png(game->tex.south);
	game->west = mlx_load_png(game->tex.west);
	game->east = mlx_load_png(game->tex.east);
    if (!game->north || !game->south || !game->west || !game->east)
    {
		printf("Error \nInvalid texture\n");
		exit(EXIT_FAILURE);
	}
	free(game->tex.north);
	free(game->tex.south);
	free(game->tex.east);
	free(game->tex.west);
}

int	check_arg_and_map(char **ar, int ac, t_game *game)
{
	int		fd;
	char	**full_file;

	if (ac != 2)
		return (write_wrong_num_ar(ac));
	if (check_map_format(ar[1]) == -1)
		return (1);
	fd = open(ar[1], O_RDWR);
	if (fd == -1)
		return (printf("Error \nInvalid map : map does not exist\n"));
	full_file = read_map(fd);
	game->tex = read_texture_data(full_file);
	load_tex(game);
	game->map = extract_map_from_file(full_file);
	free_tab(full_file);
	return (0);
}
