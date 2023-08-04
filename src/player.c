/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chabrune <chabrune@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:51:19 by chabrune          #+#    #+#             */
/*   Updated: 2023/08/02 17:19:05 by chabrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_pos(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'E'
				|| game->map[i][j] == 'W' || game->map[i][j] == 'S')
			{
				game->player.coord.x = j * B_S;
				game->player.coord.y = i * B_S;
			}
		}
	}
	init_player_direction(game);
}

void	init_player_direction(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'N')
				game->player.angle = PI / 2;
			else if (game->map[i][j] == 'E')
				game->player.angle = PI;
			else if (game->map[i][j] == 'W')
				game->player.angle = 0;
			else if (game->map[i][j] == 'S')
				game->player.angle = 3 * PI / 2;
		}
	}
}
