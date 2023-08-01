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

int    *load_col(t_game *game, int i, char *path)
{
    mlx_texture_t *tex = mlx_load_png(path);
    int *col;
    float k;
    int j = 0;
    int tmp = 0;

    col = ft_calloc((int)game->lineH[i], sizeof(int));
    if (game->side[i] == 0 || game->side[i] == 1)
    {
        if (game->ray[0][i].r.x < 0)
            tmp = game->map_height * MINIMAP_BLOC_SIZE;
        tmp = (tmp + (int)game->ray[0][i].r.x) % MINIMAP_BLOC_SIZE;
        k = (tmp + (game->ray[0][i].r.x - (int)game->ray[0][i].r.x)) * tex->width / MINIMAP_BLOC_SIZE;
    }
    else
    {
        if (game->ray[1][i].r.y < 0)
            tmp = game->map_width * MINIMAP_BLOC_SIZE;
        tmp = (tmp + (int)game->ray[1][i].r.y) % MINIMAP_BLOC_SIZE;
        k = (tmp + (game->ray[1][i].r.y - (int)game->ray[1][i].r.y)) * tex->width / MINIMAP_BLOC_SIZE;
    }
    double offset;
    double ratio;
    int test = 0;
    ratio = tex->height / game->lineH[i];
    offset = 0;
    while (j < (int)game->lineH[i])
    {
        col[j] = get_rgba(tex->pixels[test + (int)k * tex->bytes_per_pixel], tex->pixels[test + (int)k * tex->bytes_per_pixel + 1], tex->pixels[test + (int)k * tex->bytes_per_pixel + 2], tex->pixels[test + (int)k * tex->bytes_per_pixel + 3]);
        j++;
        offset += ratio;
        test = (int)offset * tex->height * tex->bytes_per_pixel;
    }
    mlx_delete_texture(tex);
    return (col);
}

void    draw_column(t_game *game, int i)
{
    float line_o;
    char *path;
    
	if (game->side[i] == 0)
        path = game->tex.south;
	if (game->side[i] == 1)
        path = game->tex.north;
	if (game->side[i] == 2)
        path = game->tex.east;
	if (game->side[i] == 3)
        path = game->tex.west;
    game->lineH[i] = DISPLAY_HEIGHT * MINIMAP_BLOC_SIZE / game->dist_ray[i];
    line_o = (game->lineH[i] - DISPLAY_HEIGHT) / 2 ;
    if (line_o < 0)
        line_o = -line_o;
    if (game->lineH[i] > DISPLAY_HEIGHT)
		game->lineH[i] = DISPLAY_HEIGHT;
	if (game->lineH[i] + line_o > DISPLAY_HEIGHT)
		line_o = 0;
    int *col;
    col = load_col(game, i, path);
    int j = -1;
    while (++j < (int)game->lineH[i])
        mlx_put_pixel(game->window, i, j + line_o, col[j]);
    draw_floor_sky(game , i, line_o);
    free(col);
}
