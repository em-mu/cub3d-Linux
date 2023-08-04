/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:29:02 by chabrune          #+#    #+#             */
/*   Updated: 2023/08/02 17:25:34 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_player_pixel(t_game *game)
{
	uint32_t	i;
	uint32_t	j;
	int			color;

	i = 0;
	while (i < ((uint32_t)game->map_height * B_S))
	{
		j = 0;
		while (j < ((uint32_t)game->map_width * B_S))
		{
			if (j == (uint32_t)game->player.coord.x
				|| i == (uint32_t)game->player.coord.y)
			{
				color = get_rgba(255, 0, 0, 255);
				put_pixel_player(game, (game->player.coord.x
						- (game->player.coord.x) + (8 * B_S)) / 2,
						(game->player.coord.y - (game->player.coord.y) + (8
						* B_S)) / 2, color);
				put_pixel_ray(game, color);
			}
			j++;
		}
		i++;
	}
}

void	put_pixel_player(t_game *game, uint32_t x, uint32_t y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < PLAYER_SIZE / 2)
	{
		j = -1;
		while (++j < PLAYER_SIZE / 2)
			mlx_put_pixel(game->window, (x + i), (y + j), color);
	}
}

void	put_pixel_ray(t_game *game, int color)
{
	int	i;

	game->rdx = game->player.coord.x + (PLAYER_SIZE / 2);
	game->rdy = game->player.coord.y + (PLAYER_SIZE / 2);
	i = -1;
	while (++i < 15)
	{
		game->rdx += -cosf(game->player.angle);
		game->rdy += -sinf(game->player.angle);
		mlx_put_pixel(game->window, (game->rdx - (game->player.coord.x) + (8
				* B_S)) / 2, (game->rdy - (game->player.coord.y) + (8
				* B_S)) / 2, color);
	}
}
