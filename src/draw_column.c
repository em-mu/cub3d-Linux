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
    (void)i;
    (void)line_o;
    (void)game;

    uint32_t j = -1; 
    while (++j < tex->height * tex->width * tex->bytes_per_pixel)
        printf("%d  ", tex->pixels[j]);
}
void    draw_floor_sky(t_game *game, int i, int line_o)
{
    int j;
    j = -1;
    int color_ceiling = get_rgba(game->tex.ceiling[0], game->tex.ceiling[1], game->tex.ceiling[2], 255);
    int color_floor = get_rgba(game->tex.floor[0], game->tex.floor[1], game->tex.floor[2], 255);
    while (++j < line_o)
        mlx_put_pixel(game->window, i , j, color_ceiling);
    j = DISPLAY_HEIGHT;
    while (--j >= game->lineH[i] + line_o - 1)
        mlx_put_pixel(game->window, i , j, color_floor);
}

void    draw_column(t_game *game, int i)
{
    float line_o;
    // char *path;
    
	// if (game->side[i] == 0)
    //     path = game->tex.north;
	// if (game->side[i] == 1)
    //     path = game->tex.south;
	// if (game->side[i] == 2)
    //     path = game->tex.east;
	// if (game->side[i] == 3)
    //     path = game->tex.west;
    game->lineH[i] = DISPLAY_HEIGHT * MINIMAP_BLOC_SIZE / game->dist_ray[i];
    line_o = (game->lineH[i] - DISPLAY_HEIGHT) / 2 ;
    if (line_o < 0)
        line_o = -line_o;
    if (game->lineH[i] > DISPLAY_HEIGHT)
		game->lineH[i] = DISPLAY_HEIGHT;
	if (game->lineH[i] + line_o > DISPLAY_HEIGHT)
		line_o = 0;
    // draw_texture(game, path, i, line_o);
    draw_floor_sky(game , i, line_o);
}
