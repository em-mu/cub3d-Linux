/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 15:19:12 by emuller           #+#    #+#             */
/*   Updated: 2023/08/04 16:48:02 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	*fill_colunm_color(t_game *game, mlx_texture_t *tex, int i, int k)
{
	double	offset;
	int		*col;
	int		test;
	int		j;
	int		index;

	test = 0;
	offset = 1;
	j = -1;
	col = ft_calloc((int)game->line_h[i], sizeof(int));
	if (game->line_h[i] > DISPLAY_HEIGHT)
		offset = (game->line_h[i] - DISPLAY_HEIGHT) / 2;
	game->ratio = tex->height / game->line_h[i];
	offset *= game->ratio;
	while (++j < (int)game->line_h[i])
	{
		index = test + (int)k * 4;
		if (index >= 0 && index + 3 < (int)tex->height * (int)tex->width
			* tex->bytes_per_pixel)
			col[j] = get_rgba(tex->pixels[index], tex->pixels[index + 1],
					tex->pixels[index + 2], tex->pixels[index + 3]);
		offset += game->ratio;
		test = (int)offset * tex->height * 4;
	}
	return (col);
}

int	*load_col(t_game *game, int i, mlx_texture_t *tex)
{
	int		*col;
	float	k;

	if (game->side[i] == 0 || game->side[i] == 1)
		k = calculate_step(game, tex, game->ray[0][i].r.x);
	else
		k = calculate_step(game, tex, game->ray[1][i].r.y);
	if (game->side[i] == 0 || game->side[i] == 3)
		k = tex->width - k;
	col = fill_colunm_color(game, tex, i, k);
	return (col);
}

int	*load_side(t_game *game, int i)
{
	int	*col;

	col = 0;
	if (game->side[i] == 1)
		col = load_col(game, i, game->north);
	else if (game->side[i] == 0)
		col = load_col(game, i, game->south);
	else if (game->side[i] == 2)
		col = load_col(game, i, game->east);
	else if (game->side[i] == 3)
		col = load_col(game, i, game->west);
	return (col);
}

void	draw_column(t_game *game, int i)
{
	float	line_o;
	int		*col;
	int		j;

	game->line_h[i] = DISPLAY_HEIGHT * B_S / game->dist_ray[i];
	line_o = (game->line_h[i] - DISPLAY_HEIGHT) / 2;
	col = load_side(game, i);
	if (game->line_h[i] > DISPLAY_HEIGHT)
		game->line_h[i] = DISPLAY_HEIGHT;
	if (line_o < 0)
		line_o = -line_o;
	if (game->line_h[i] + line_o > DISPLAY_HEIGHT)
		line_o = 0;
	j = -1;
	while (++j < (int)game->line_h[i])
		mlx_put_pixel(game->window, i, j + line_o, col[j]);
	draw_floor_sky(game, i, line_o);
	free(col);
	col = NULL;
}
