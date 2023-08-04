/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:47:33 by emuller           #+#    #+#             */
/*   Updated: 2023/08/02 17:39:11 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	collision(t_game *game, float angle)
{
	int		x;
	int		y;
	float	testx;
	float	testy;

	testx = game->player.coord.x + cos(game->player.angle + angle) * SPEED;
	testy = game->player.coord.y + sin(game->player.angle + angle) * SPEED;
	x = (int)(testx) / B_S;
	y = (int)(testy) / B_S;
	if (game->map[y][x] == '1')// || ( game->map[(int)game->player.coord.y/B_S][x] == '1' && game->map[y][(int)game->player.coord.x/B_S] == '1'))
		return (1);
	return (0);
}

float	adjust_angle(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

void	check_angle(t_game *game)
{
	int	i;

	i = -1;
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	if (game->player.angle > 2 * PI)
		game->player.angle -= 2 * PI;
	while (++i < 60)
	{
		if (game->ray[0][i].angle < 0)
			game->ray[0][i].angle += 2 * PI;
		if (game->ray[0][i].angle > 2 * PI)
			game->ray[0][i].angle -= 2 * PI;
		if (game->ray[1][i].angle < 0)
			game->ray[1][i].angle += 2 * PI;
		if (game->ray[1][i].angle > 2 * PI)
			game->ray[1][i].angle -= 2 * PI;
	}
}
