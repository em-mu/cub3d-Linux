/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:47:33 by emuller           #+#    #+#             */
/*   Updated: 2023/07/10 18:36:11 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	collision(t_game *game, float angle)
{
	int x;
	int y;
	float testx;
	float testy;

	testx = game->player.coord.x + cos(game->player.angle + angle) * SPEED;
	testy = game->player.coord.y + sin(game->player.angle + angle) * SPEED;
	x = (int)(testx) / MINIMAP_BLOC_SIZE;
	y = (int)(testy) / MINIMAP_BLOC_SIZE;

	if (game->map[y][x] == '1')
		return (1);
	return (0);
}

float	adjust_angle(float angle)
{
	if(angle < 0)
		angle += 2 * PI;
	if(angle > 2 * PI)
		angle -= 2 * PI;
	return angle;
}

static void	check_angle(t_game *game)
{
	int i;

	i = -1;
	if(game->player.angle < 0)
		game->player.angle += 2 * PI;
	if(game->player.angle > 2 * PI)
		game->player.angle -= 2 * PI;
	while(++i < 60)
	{
		if(game->ray[0][i].angle < 0)
			game->ray[0][i].angle += 2 * PI;
		if(game->ray[0][i].angle > 2 * PI)
			game->ray[0][i].angle -= 2 * PI;
		if(game->ray[1][i].angle < 0)
			game->ray[1][i].angle += 2 * PI;
		if(game->ray[1][i].angle > 2 * PI)
			game->ray[1][i].angle -= 2 * PI;
	}
}

void	ft_key_right(t_game *game)
{
	game->player.angle += 0.1;
	check_angle(game);
}

void	ft_key_left(t_game *game)
{
	game->player.angle -= 0.1;
	check_angle(game);
}

void move_point(t_game *game, float angle)
{
	if (!collision(game, angle))
	{
		game->pdx = cos(game->player.angle + angle);
		game->pdy = sin(game->player.angle + angle);
		game->player.coord.x += game->pdx * SPEED;
		game->player.coord.y += game->pdy * SPEED;
	}
}