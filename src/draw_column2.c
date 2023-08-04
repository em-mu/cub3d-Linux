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
	while (--j >= game->line_h[i] + line_o - 1)
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
