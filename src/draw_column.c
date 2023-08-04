/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:19:12 by emuller           #+#    #+#             */
/*   Updated: 2023/08/02 18:01:48 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_sky(t_game *game, int i, int line_o)
{
	int	j;
	int	color_ceiling;
	int	color_floor;

	j = -1;
	color_ceiling = get_rgba(game->tex.ceiling[0], game->tex.ceiling[1],
			game->tex.ceiling[2], 255);
	color_floor = get_rgba(game->tex.floor[0], game->tex.floor[1],
			game->tex.floor[2], 255);
	while (++j < line_o)
		mlx_put_pixel(game->window, i, j, color_ceiling);
	j = DISPLAY_HEIGHT;
	while (--j >= game->lineH[i] + line_o - 1)
		mlx_put_pixel(game->window, i, j, color_floor);
}

float	calculate_step(t_game *game, mlx_texture_t *tex, double ray)
{
	float	k;
	int		tmp;

	tmp = 0;
	if (ray < 0)
		tmp = game->map_height * B_S;
	tmp = (tmp + (int)ray) % B_S;
	k = (tmp + (ray - (int)ray)) * tex->width / B_S;
	return (k);
}

// void	fill_colunm_color()
// {
// 	double	offset;
// 	double	ratio;
// 	int		test;
// }

int		*load_col(t_game *game, int i, mlx_texture_t *tex)
{
	int		*col;
	float	k;
	int		j;
	double	offset;
	double	ratio;
	int		test;

	j = 0;
	col = ft_calloc((int)game->lineH[i], sizeof(int));
	if (game->side[i] == 0 || game->side[i] == 1)
		k = calculate_step(game, tex, game->ray[0][i].r.x);
	else
		k = calculate_step(game, tex, game->ray[1][i].r.y);
	if (game->side[i] == 0 || game->side[i] == 3)
		k = tex->width - 1 - k;
	test = 0;
	offset = 1;
	if (game->lineH[i] > DISPLAY_HEIGHT)
		offset = (game->lineH[i] - DISPLAY_HEIGHT) / 2;
	ratio = tex->height / game->lineH[i];
	offset *= ratio;
	 while (j < (int)game->lineH[i])
    {
        col[j] = get_rgba(tex->pixels[test + (int)k * tex->bytes_per_pixel], tex->pixels[test + (int)k * tex->bytes_per_pixel + 1], tex->pixels[test + (int)k * tex->bytes_per_pixel + 2], tex->pixels[test + (int)k * tex->bytes_per_pixel + 3]);
        j++;
        offset += ratio;
        test = (int)offset * tex->height * tex->bytes_per_pixel;
    }
	return (col);
}

void	draw_column(t_game *game, int i)
{
	float	line_o;
	int		*col;
	int		j;

	col = 0;
	game->lineH[i] = DISPLAY_HEIGHT * B_S / game->dist_ray[i];
	line_o = (game->lineH[i] - DISPLAY_HEIGHT) / 2;
	if (game->side[i] == 1)
		col = load_col(game, i, game->north);
	else if (game->side[i] == 0)
		col = load_col(game, i, game->south);
	else if (game->side[i] == 2)
		col = load_col(game, i, game->east);
	else if (game->side[i] == 3)
		col = load_col(game, i, game->west);
	if (game->lineH[i] > DISPLAY_HEIGHT)
		game->lineH[i] = DISPLAY_HEIGHT;
	if (line_o < 0)
		line_o = -line_o;
	if (game->lineH[i] + line_o > DISPLAY_HEIGHT)
		line_o = 0;
	j = -1;
	while (++j < (int)game->lineH[i])
		mlx_put_pixel(game->window, i, j + line_o, col[j]);
	draw_floor_sky(game, i, line_o);
	free(col);
	col = NULL;
}
