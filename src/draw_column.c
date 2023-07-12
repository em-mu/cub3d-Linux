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
    
    game->lineH[i] = DISPLAY_HEIGHT * 10 / game->dist_ray[i];
    line_o = game->lineH[i] / 2 ;
    if (game->lineH[i] > DISPLAY_HEIGHT)
        game->lineH[i] = DISPLAY_HEIGHT;
    if (game->lineH[i] + line_o > DISPLAY_HEIGHT)
        line_o = 0;
    
    int j;
    j = -1;
    while (++j < game->lineH[i])
        mlx_put_pixel(game->window, i + 400 , j + line_o, get_rgba(255,255,255,255));
}