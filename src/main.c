/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:52:47 by emuller           #+#    #+#             */
/*   Updated: 2023/08/02 17:45:36 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	delete_texture(t_game *game)
{
	(void)game;
	// mlx_delete_texture(game->north);
	// mlx_delete_texture(game->west);
	// mlx_delete_texture(game->east);
	// mlx_delete_texture(game->south);
	// free_tab(game->map);
}

int	open_window(t_game *game)
{
	init_player_pos(game);
	get_map_dimensions(game->map, game);
	game->mlx = mlx_init(DISPLAY_WIDTH, DISPLAY_HEIGHT, "cub3d", true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->window = mlx_new_image(game->mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	mlx_image_to_window(game->mlx, game->window, 0, 0);
	mlx_loop_hook(game->mlx, ft_hook, game);
	mlx_loop(game->mlx);
	delete_texture(game);
	mlx_terminate(game->mlx);
	return (EXIT_SUCCESS);
}

void	init_game(t_game *game)
{
	int	i;

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
