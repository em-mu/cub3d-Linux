/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:08:21 by emuller           #+#    #+#             */
/*   Updated: 2023/06/05 17:34:23 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	write_wrong_num_ar(int ar)
{
	if (ar == 1)
		printf("Error \ncub3d needs a map to run\n");
	if (ar >= 3)
		printf("Error \ncub3d can only read one map\n");
	return (1);
}

void	exit_error(char **map, char *msg)
{
	if (msg)
		printf("Error \n%s\n", msg);
	if (map)
		free_tab(map);
	exit(1);
}
