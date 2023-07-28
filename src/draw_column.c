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

void    draw_texture(t_game *game, char *path, int i, int line_o)
{
    mlx_texture_t *tex = mlx_load_png(path);
	uint32_t j = 0;
	uint32_t k = 0;

	int	col[64][64*4];
	while (j < tex->height)
	{
		while (k < tex->width * tex->bytes_per_pixel)
		{
			col[j][k] = tex->pixels[k];
			k++;
		}
		j++;
	}
    int t = 0;
    uint32_t test;
    k = -1;
    while (++k < game->lineH[i])
    {
        test = 0;
        while (test < tex->width)
        {
            mlx_put_pixel(game->window, i, k + line_o, get_rgba(col[test][t], col[test][t+1], col[test][t+2], col[test][t+3]));
            test++;
        }
        t += 4;
    }
}

void    draw_column(t_game *game, int i)
{
    float line_o;
    char *path;
    
	// int color = 0;
	if (game->side[i] == 0)
        path = game->tex.north;
		// color = get_rgba(255,255,255,255);
	if (game->side[i] == 1)
        path = game->tex.south;
		// color = get_rgba(200,0,200,255);
	if (game->side[i] == 2)
        path = game->tex.east;
		// color = get_rgba(150,150,0,255);
	if (game->side[i] == 3)
        path = game->tex.west;
		// color = get_rgba(0,100,100,255);
    game->lineH[i] = DISPLAY_HEIGHT * MINIMAP_BLOC_SIZE / game->dist_ray[i];
    line_o = (game->lineH[i] - DISPLAY_HEIGHT) / 2 ;
    if (line_o < 0)
        line_o = -line_o;
    if (game->lineH[i] > DISPLAY_HEIGHT)
		game->lineH[i] = DISPLAY_HEIGHT;
	if (game->lineH[i] + line_o > DISPLAY_HEIGHT)
		line_o = 0;
	int j;
    draw_texture(game, path, i, line_o);
    // j = -1;
    // while (++j < game->lineH[i])
    // {
    //      mlx_put_pixel(game->window, i , j + line_o, color);
    // }
    j = -1;
    int color_ceiling = get_rgba(game->tex.ceiling[0], game->tex.ceiling[1], game->tex.ceiling[2], 255);
    int color_floor = get_rgba(game->tex.floor[0], game->tex.floor[1], game->tex.floor[2], 255);
    while (++j < line_o)
        mlx_put_pixel(game->window, i , j, color_ceiling);
    j = DISPLAY_HEIGHT;
    while (--j >= game->lineH[i] + line_o - 1)
        mlx_put_pixel(game->window, i , j, color_floor);
}
