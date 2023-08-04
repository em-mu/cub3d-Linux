/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
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
	float	x;
	float	y;
	float	testx;
	float	testy;

	testx = game->ray[i][j].r.x;
	testy = game->ray[i][j].r.y;
	x = testx / B_S;
	y = testy / B_S;
	if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height)
	{
		if (game->map[(int)y][(int)x] == '1')
			return (1);
	}
	return (0);
}

int	add_offset_vert(t_game *game, int i)
{
	if (game->ray[1][i].r.x < 0 || game->ray[1][i].r.x >= DISPLAY_WIDTH
		|| game->ray[1][i].r.y < 0 || game->ray[1][i].r.y >= DISPLAY_HEIGHT)
		return (1);
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

int	add_offset_hori(t_game *game, int i)
{
	if (game->ray[0][i].r.x < 0 || game->ray[0][i].r.x >= DISPLAY_WIDTH
		|| game->ray[0][i].r.y < 0 || game->ray[0][i].r.y >= DISPLAY_HEIGHT)
		return (1);
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

	distance_wall = 100000000;
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

double	calculate_rayon_horizontal(t_game *game, int i)
{
	float	h;
	double	distance_wall;
	double	artan;

	distance_wall = 100000000;
	game->ray[0][i].angle = game->player.angle - (N_RAY / 2 * DR - (i * DR));
	game->ray[0][i].angle = adjust_angle(game->ray[0][i].angle);
	game->ray[0][i].r.x = game->player.coord.x;
	game->ray[0][i].r.y = game->player.coord.y;
	game->ray[0][i].o.y = B_S;
	game->ray[0][i].o.x = B_S / tanf(game->ray[0][i].angle);
	artan = -1 / tanf(game->ray[0][i].angle);
	if (game->ray[0][i].angle < PI)
	{
		game->ray[0][i].r.y = ((int)(game->player.coord.y / B_S) * B_S)
			- 0.0001;
		h = (game->player.coord.y - game->ray[0][i].r.y);
		if (h < 0)
			h = -h;
		game->ray[0][i].r.x = game->player.coord.x + (h * artan);
	}
	if (game->ray[0][i].angle > PI)
	{
		game->ray[0][i].r.y = ((int)(game->player.coord.y / B_S) * B_S) + B_S;
		h = (game->ray[0][i].r.y - game->player.coord.y);
		if (h < 0)
			h = -h;
		game->ray[0][i].r.x = game->player.coord.x - (h * artan);
	}
	distance_wall = check_walls(game, i, 0);
	return (distance_wall);
}

double	calculate_rayon_vertical(t_game *game, int i)
{
	float	h;
	double	distance_wall;

	game->ray[1][i].angle = game->player.angle - (N_RAY / 2 * DR - (i * DR));
	game->ray[1][i].angle = adjust_angle(game->ray[1][i].angle);
	game->ray[1][i].r.x = game->player.coord.x;
	game->ray[1][i].r.y = game->player.coord.y;
	game->ray[1][i].o.x = B_S;
	game->ray[1][i].o.y = B_S * tanf(game->ray[1][i].angle);
	if (game->ray[1][i].angle < (PI / 2) || game->ray[1][i].angle > (3 * PI
			/ 2))
	{
		game->ray[1][i].r.x = (int)((int)(game->player.coord.x / B_S) * B_S)
			- 0.0001;
		h = (game->player.coord.x - game->ray[1][i].r.x);
		if (h < 0)
			h = -h;
		game->ray[1][i].r.y = game->player.coord.y - h
			* tanf(game->ray[1][i].angle);
	}
	if (game->ray[1][i].angle > (PI / 2) && game->ray[1][i].angle < (3 * PI
			/ 2))
	{
		game->ray[1][i].r.x = (int)((int)(game->player.coord.x / B_S) * B_S)
			+ B_S;
		h = (game->player.coord.x - game->ray[1][i].r.x);
		if (h < 0)
			h = -h;
		game->ray[1][i].r.y = game->player.coord.y + h
			* tanf(game->ray[1][i].angle);
	}
	distance_wall = check_walls(game, i, 1);
	return (distance_wall);
}
