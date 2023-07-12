/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:52:47 by emuller           #+#    #+#             */
/*   Updated: 2023/07/11 15:46:03 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	open_window(t_game *game)
{
	init_player_pos(game);
	get_map_dimensions(game->map, game);
	game->mlx = mlx_init(DISPLAY_WIDTH, DISPLAY_HEIGHT, "cub3d", false);
	game->window = mlx_new_image(game->mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	mlx_image_to_window(game->mlx, game->window, 0, 0);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}

void	print_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

void	init_game(t_game *game)
{
	int i;

	game->map = NULL;
	game->mlx = NULL;
	game->window = NULL;
	game->player.coord.x = 0;
	game->player.coord.y = 0;
	game->map_width = 0;
	game->map_height = 0;
	i = -1;
	while (++i < N_RAY)
	{
		game->dist_ray[i] = 0;
		game->lineH[i] = 0;
		game->side[i] = 0;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	init_game(&game);
	if (check_arg_and_map(argv, argc, &game))
		return (1);
	if (open_window(&game) == 1)
	{
		printf("Error\n");
		return (1);
	}
	return (0);
}
