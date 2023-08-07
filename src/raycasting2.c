/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:51:02 by emuller           #+#    #+#             */
/*   Updated: 2023/08/02 17:19:05 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	coll_ray(t_game *game, int i, int j)
{
	double	x;
	double	y;
	double	testx;
	double	testy;

	testx = game->ray[i][j].r.x;
	testy = game->ray[i][j].r.y;
	x = testx / B_S;
	y = testy / B_S;
	if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height)
	{
		if (game->map[(int)y][(int)x] == '1')
			return (1);
	}
	else 
		return (-1);
	return (0);
}

static int	add_offset_vert(t_game *game, int i)
{
	// if (game->ray[1][i].r.x < 0 || game->ray[1][i].r.x >= DISPLAY_WIDTH
	// 	|| game->ray[1][i].r.y < 0 || game->ray[1][i].r.y >= DISPLAY_HEIGHT)
	// 	return (1);
	if (game->ray[1][i].angle > (PI / 2) && game->ray[1][i].angle < (3 * PI
			/ 2))
	{
		game->ray[1][i].r.x += game->ray[1][i].o.x;
		game->ray[1][i].r.y += game->ray[1][i].o.y;
	}
	if (game->ray[1][i].angle < (PI / 2) || game->ray[1][i].angle > (3 * PI
			/ 2))
	{
		game->ray[1][i].r.x -= game->ray[1][i].o.x;
		game->ray[1][i].r.y -= game->ray[1][i].o.y;
	}
	return (0);
}

static int	add_offset_hori(t_game *game, int i)
{
	// if (game->ray[0][i].r.x < 0 || game->ray[0][i].r.x >= DISPLAY_WIDTH
	// 	|| game->ray[0][i].r.y < 0 || game->ray[0][i].r.y >= DISPLAY_HEIGHT)
	// 	return (1);
	if (game->ray[0][i].angle < PI)
	{
		game->ray[0][i].r.x -= game->ray[0][i].o.x;
		game->ray[0][i].r.y -= game->ray[0][i].o.y;
	}
	else if (game->ray[0][i].angle > PI)
	{
		game->ray[0][i].r.x += game->ray[0][i].o.x;
		game->ray[0][i].r.y += game->ray[0][i].o.y;
	}
	return (0);
}

float	check_walls(t_game *game, int i, int side)
{
	double	distance_wall;

	distance_wall = 10000000000.0;
	while (1)
	{
		if (coll_ray(game, side, i))
		{
			distance_wall = sqrt(((game->ray[side][i].r.x
							- game->player.coord.x) * (game->ray[side][i].r.x
							- game->player.coord.x)) + (game->ray[side][i].r.y
						- game->player.coord.y) * (game->ray[side][i].r.y
						- game->player.coord.y));
			break ;
		}
		else
		{
			if (side == 1)
				if (add_offset_vert(game, i) == 1)
					break ;
			if (side == 0)
				if (add_offset_hori(game, i) == 1)
					break ;
		}
	}
	return (distance_wall);
}
