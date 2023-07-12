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

void    draw_column(t_game *game, int i)
{
    double line_o;
    
    game->lineH[i] = DISPLAY_HEIGHT * 12 / game->dist_ray[i];
    line_o =  fabs(DISPLAY_HEIGHT - game->lineH[i]) / 2 ;
    if (game->lineH[i] > DISPLAY_HEIGHT)
        game->lineH[i] = DISPLAY_HEIGHT;
    if (game->lineH[i] + line_o > DISPLAY_HEIGHT)
        line_o = 0;

    int j;
    j = -1;
    while (++j < game->lineH[i])
        mlx_put_pixel(game->window, i , j + line_o, get_rgba(255,255,255,255));
    j = -1;
    while (++j < line_o)
        mlx_put_pixel(game->window, i , j, get_rgba(50,130,28,255));
    j = DISPLAY_HEIGHT;
    while (--j >= game->lineH[i] + line_o - 1)
        mlx_put_pixel(game->window, i , j, get_rgba(147,200,28,255));

}