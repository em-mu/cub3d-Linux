/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:29:02 by chabrune          #+#    #+#             */
/*   Updated: 2023/07/10 14:56:15 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	put_pixel_map(t_game *game, uint32_t x, uint32_t y, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < MINIMAP_BLOC_SIZE)
	{
		j = -1;
		while (++j < MINIMAP_BLOC_SIZE)
			mlx_put_pixel(game->window, x + i, y + j, color);
	}
}

void	put_map_pixel(t_game *game)
{
	uint32_t i;
	uint32_t j;
	int color;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == '1')
				color = get_rgba(0, 0, 255, 255);
			else if (game->map[i][j] == '0')
				color = get_rgba(0, 0, 0, 255);
    		put_pixel_map(game, j * MINIMAP_BLOC_SIZE, i * MINIMAP_BLOC_SIZE, color);
		}
	}
}

void	put_player_pixel(t_game *game)
{
	uint32_t i;
	uint32_t j;
	int color;

	i = 0;
	while (i < ((uint32_t)game->map_height * MINIMAP_BLOC_SIZE))
	{
		j = 0;
		while (j < ((uint32_t)game->map_width * MINIMAP_BLOC_SIZE))
		{
			if (j == (uint32_t)game->player.coord.x || i == (uint32_t)game->player.coord.y)
			{
				color = get_rgba(255, 0, 0, 255);
				put_pixel_player(game, game->player.coord.x , game->player.coord.y , color);
				put_pixel_ray(game, color);
			}
			j++;
		}
		i++;
	}
}

void	put_pixel_player(t_game *game, uint32_t x, uint32_t y, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < PLAYER_SIZE)
	{
		j = -1;
		while (++j < PLAYER_SIZE)
			mlx_put_pixel(game->window, x + i, y + j, color);
	}
}

void	put_pixel_ray(t_game *game, int color)
{
	game->rdx = game->player.coord.x + (PLAYER_SIZE / 2);
	game->rdy = game->player.coord.y + (PLAYER_SIZE / 2);
	int i = -1;
	while(++i < 10)
	{
		game->rdx += -cosf(game->player.angle);
		game->rdy += -sinf(game->player.angle);
		mlx_put_pixel(game->window, game->rdx, game->rdy, color);
	}
}
