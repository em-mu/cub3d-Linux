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

void	find_shortest_ray(t_game *game, int i, double distH, double distV)
{
	float r1;
	float r2;
	
	r1 = 0;
	r2 = 0;
	if(distH < distV)
	{
		r1 = game->ray[0][i].r.x;
		r2 = game->ray[0][i].r.y;
		game->dist_ray[i] = distH;
	}
	else 
	{
		r1 = game->ray[1][i].r.x;
		r2 = game->ray[1][i].r.y;
		game->dist_ray[i] = distV;
	}
	
	// game->rdx = game->player.coord.x + (PLAYER_SIZE / 2);
    // game->rdy = game->player.coord.y + (PLAYER_SIZE / 2);
	// int j = 0;
    // while(j++ < 1000 && (int)r1+1 != (int)game->rdx && (int)r2+1 != (int)game->rdy)
    // {
    //     game->rdx -= cosf(game->ray[0][i].angle);
    //     game->rdy -= sinf(game->ray[0][i].angle);
    //     mlx_put_pixel(game->window, game->rdx, game->rdy, get_rgba(255,255,255,255));
    // }
	
	int k = 0;
	while (k < 2)
	{
		int j = -1;
		while (++j < 2)
			mlx_put_pixel(game->window, r1 , r2 , get_rgba(255,255,255,255));
		k++;
	}
}


void	ft_hook(void *param)
{
	t_game	*game;
	double distH = 0;
	double distV = 0;

	game = (t_game *)param;
	update_position(game);
	mlx_delete_image(game->mlx, game->window);
	game->window = mlx_new_image(game->mlx, DISPLAY_WIDTH, DISPLAY_HEIGHT);
	int i = 0;
	while (i < N_RAY)
	{
		distH = calculate_rayon_horizontal(game, i);
		distV = calculate_rayon_vertical(game, i);
		find_shortest_ray(game, i, distH, distV);
		i++;
	}
	i = 0;
	while (i < N_RAY)
	{
		draw_column(game, i);
		draw_column(game, i+1);
		i += 2;
	}
	put_map_pixel(game);
	put_player_pixel(game);
	mlx_image_to_window(game->mlx, game->window, 0, 0);
}
