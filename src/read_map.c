/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:19:37 by emuller           #+#    #+#             */
/*   Updated: 2023/06/24 17:07:27 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_list	*create_list_from_map(t_list *lst, int fd)
{
	t_list	*tmp;
	char	*s;

	s = get_next_line(fd);
	if (!s)
	{
		printf("Error \nInvalid file: empty file\n");
		exit(EXIT_FAILURE);
	}
	while (s)
	{
		tmp = ft_lstnew(s);
		ft_lstadd_back(&lst, tmp);
		s = get_next_line(fd);
	}
	return (lst);
}

char	**read_map(int fd)
{
	char	**map;
	t_list	*lst;
	t_list	*tmp;
	int		i;

	lst = NULL;
	lst = create_list_from_map(lst, fd);
	map = ft_calloc(sizeof(char *), (ft_lstsize(lst) + 1));
	if (!map)
	{
		printf("Error\n malloc error\n");
		ft_lstclear(&lst, free);
		exit(EXIT_FAILURE);
	}
	i = 0;
	tmp = lst;
	while (tmp)
	{
		map[i++] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&lst, free);
	return (map);
}

int	find_map_len(int i, char **map)
{
	int	len;

	len = 0;
	while (map[i])
	{
		i++;
		len++;
	}
	if (len == 0)
	{
		printf("Error \nInvalid map: no map in file\n");
		free_tab(map);
		exit(1);
	}
	return (len);
}

int	find_beginning_map(char *str)
{
	int	i;

	i = 0;
	if (!str[i] || !str)
		return (0);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == 0)
		return (0);
	i = 0;
	while (str[i] && (str[i] == '1' || str[i] == '0' || str[i] == ' '
			|| str[i] == '\t'))
		i++;
	if (str[i] == 0)
		return (1);
	return (0);
}

int	find_end_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	i--;
	while (map[i] && line_empty(map[i]) == 1)
		i--;
	return (++i);
}
