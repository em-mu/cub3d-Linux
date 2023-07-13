/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:19:12 by emuller           #+#    #+#             */
/*   Updated: 2023/07/11 16:17:55 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    draw_column(t_game *game, int i, int Q)
{
    float line_o;
    
	int color = 0;
	if (game->side[i] == 0)
		color = get_rgba(255,255,255,255);
	if (game->side[i] == 1)
		color = get_rgba(200,0,200,255);
	if (game->side[i] == 2)
		color = get_rgba(150,150,0,255);
	if (game->side[i] == 3)
		color = get_rgba(0,100,100,255);
    game->lineH[i] = game->display_height * 12 / game->dist_ray[i];
    line_o = (game->lineH[i] - game->display_height) / 2 ;
    if (line_o < 0)
        line_o = -line_o;
    if (game->lineH[i] > game->display_height)
		game->lineH[i] = game->display_height;
	if (game->lineH[i] + line_o > game->display_height)
		line_o = 0;
	int j;
    j = -1;
    while (++j < game->lineH[i])
        mlx_put_pixel(game->window, Q , j + line_o, color);
    j = -1;
    int color_ceiling = get_rgba(game->tex.ceiling[0], game->tex.ceiling[1], game->tex.ceiling[2], 255);
    int color_floor = get_rgba(game->tex.floor[0], game->tex.floor[1], game->tex.floor[2], 255);
    while (++j < line_o)
        mlx_put_pixel(game->window, Q , j, color_ceiling);
    j = game->display_height;
    while (--j >= game->lineH[i] + line_o - 1)
        mlx_put_pixel(game->window, Q , j, color_floor);
}
