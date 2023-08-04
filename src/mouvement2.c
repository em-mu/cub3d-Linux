/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:47:33 by emuller           #+#    #+#             */
/*   Updated: 2023/08/02 17:11:05 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_key_right(t_game *game)
{
	game->player.angle += 0.1;
	check_angle(game);
}

void	ft_key_left(t_game *game)
{
	game->player.angle -= 0.1;
	check_angle(game);
}

void	move_point(t_game *game, float angle)
{
	if (!collision(game, angle))
	{
		game->pdx = cos(game->player.angle + angle);
		game->pdy = sin(game->player.angle + angle);
		game->player.coord.x += game->pdx * SPEED;
		game->player.coord.y += game->pdy * SPEED;
	}
}
