/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:39:42 by emuller           #+#    #+#             */
/*   Updated: 2023/06/05 17:16:37 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
char	*ft_read_save(int fd, char *tmp);
char	*ft_get_line(char *tmp);
char	*ft_after_nl(char *tmp);
void	ft_strlcpy2(char *dst, char *src, size_t dstsize);
char	*ft_strjoin2(char *s1, char *s2);
int		ft_strchr2(char *s, int c);
char	*ft_free_init(char **s);

#endif
