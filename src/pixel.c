/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:29:02 by chabrune          #+#    #+#             */
/*   Updated: 2023/08/02 17:21:20 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	put_pixel_map(t_game *game, uint32_t x, uint32_t y, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < B_S / 2)
	{
		j = -1;
		while (++j < B_S / 2)
			mlx_put_pixel(game->window, x + i - B_S / 4, y + j - B_S / 4,
					color);
	}
}

void	put_map_background(t_game *game)
{
	uint32_t	i;
	uint32_t	j;

	i = -1;
	while (++i < 8 * B_S)
	{
		j = -1;
		while (++j < 8 * B_S)
		{
			mlx_put_pixel(game->window, i, j, get_rgba(190, 240, 160, 255));
		}
	}
}

void	put_map_pixel(t_game *game)
{
	uint32_t	i;
	uint32_t	j;
	int			color;

	put_map_background(game);
	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '1')
				color = get_rgba(90, 140, 240, 255);
			else if (game->map[i][j] == '0')
				color = get_rgba(190, 200, 255, 255);
			if ((j * B_S > (uint32_t)(game->player.coord.x / B_S) * B_S - 8
					* B_S) && (j * B_S < (uint32_t)(game->player.coord.x / B_S)
					* B_S + 8 * B_S) && (i
					* B_S > (uint32_t)(game->player.coord.y / B_S) * B_S - 8
					* B_S) && (i * B_S < (uint32_t)(game->player.coord.y / B_S)
					* B_S + 8 * B_S))
			{
				put_pixel_map(game, ((j * B_S)
							- ((uint32_t)(game->player.coord.x / B_S) * B_S)
							+ (8 * B_S)) / 2, ((i * B_S)
							- ((uint32_t)(game->player.coord.y / B_S) * B_S)
							+ (8 * B_S)) / 2, color);
			}
		}
	}
}
