/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:45:31 by chabrune          #+#    #+#             */
/*   Updated: 2023/07/11 16:03:01 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_position(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		ft_key_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		ft_key_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
		move_point(game, PI);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		move_point(game, 0);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_point(game, (PI / 2));
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_point(game, (3 * PI / 2));
}

double	fish_eye(t_game *game, int k, int i, float dist)
{
	float ca;

	ca = game->ray[k][i].angle - game->player.angle;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	dist = dist * cos(ca);
	return (dist);
}

void	find_shortest_ray(t_game *game, int i, double distH, double distV)
{
	if(distH < distV)
	{
		game->dist_ray[i] = fish_eye(game, 0, i, distH);
		if (game->ray[0][i].angle > PI)
			game->side[i] = 0;
		else
			game->side[i] = 1;
	}
	else 
	{
		game->dist_ray[i] = fish_eye(game, 1, i, distV);
		if (game->ray[0][i].angle > PI/2 && game->ray[0][i].angle < 3*PI/2)
			game->side[i] = 2;
		else 
			game->side[i] = 3;
	
	}
}

void	resize_hook(int width, int height, void *param)
{
	t_game	*game;
	game = (t_game *)param;
	game->display_width = width;
	game->display_height = height;
}

void	ft_hook(void *param)
{
	t_game	*game;
	double distH = 0;
	double distV = 0;
	game = (t_game *)param;
	update_position(game);
	mlx_delete_image(game->mlx, game->window);
	game->window = mlx_new_image(game->mlx, game->display_width, game->display_height);
	int i = 0;
	while (i < N_RAY)
	{
		distH = calculate_rayon_horizontal(game, i);
		distV = calculate_rayon_vertical(game, i);
		find_shortest_ray(game, i, distH, distV);
		draw_column(game, i);
		i++;
	}
	// put_map_pixel(game);
	// put_player_pixel(game);
	mlx_image_to_window(game->mlx, game->window, 0, 0);
}
