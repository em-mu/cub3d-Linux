/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuller <emuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 14:53:38 by emuller           #+#    #+#             */
/*   Updated: 2023/07/11 16:20:22 by emuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define DISPLAY_WIDTH 1920
# define DISPLAY_HEIGHT 1080
# define MINIMAP_BLOC_SIZE 16
# define SPEED 2
# define PLAYER_SIZE MINIMAP_BLOC_SIZE/3
# define PI M_PI
# define N_RAY 1920
# define DR 0.000545415625
# include "../libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include "../MLX42/include/MLX42/MLX42.h"

# define R "\033[0;31m"

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor[3];
	int		ceiling[3];
}	t_texture;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_player
{
	float	angle;
	t_point	coord;
}	t_player;

typedef struct s_rayon
{
	float	angle;
	t_point	r;
	t_point o;
}	t_rayon;

typedef struct s_game
{
	int		    display_width;
	int			display_height;
	t_player	player;
	mlx_t		*mlx;
	mlx_image_t	*window;
	char		**map;
	int			map_width;
	int			map_height;
	t_texture	tex;
	float		pdy;
	float		pdx;
	float		rdx;
	float		rdy;
	t_rayon		ray[2][N_RAY];
	double		dist_ray[N_RAY];
	double		lineH[N_RAY];
	int			side[N_RAY];
}	t_game;

//utils
void	free_tab(char **tab);
int		line_empty(char *str);
int		is_valid_char(char c);
void	exit_error(char	**map, char *msg);
void	get_map_dimensions(char **map, t_game *game);
char	**dup_tab(char **tab);
int		get_rgba(int r, int g, int b, int a);
float	adjust_angle(float angle);

// Parsing de la map
int		check_map_format(char *s);
int		write_wrong_num_ar(int ar);
t_list	*create_list_from_map(t_list *lst, int fd);
char	**read_map(int fd);
int		find_map_len(int i, char **map);
int		find_beginning_map(char *str);
int		check_valid_line(char *str);
void	check_closed_map(int i, char **map);
int		find_end_map(char **map);
int		check_closed_around_space(char **map);
int		check_around(char **map, int i, size_t j);
char	**extract_map_from_file(char **map_full_file);
int		write_wrong_num_ar(int ar);
int		check_arg_and_map(char **ar, int ac, t_game *game);

// Parsing textures
void		check_tex_num(char 	**file);
void		fill_tex_data(t_texture *tex, char **file);
t_texture	read_texture_data(char	**file);

// Hook
void	ft_hook(void *param);
void	update_position(t_game *game);
void	ft_key_left(t_game *game);
void	ft_key_right(t_game *game);
void	move_point(t_game *game, float angle);

// Pixel
int		put_pixel(t_game *game, uint32_t x, uint32_t y, int color);
void 	put_map_pixel(t_game *game);

// Player
void	init_player_pos(t_game *game);
void	init_player_direction(t_game *game);
void	print_map(char **map);
void	put_player_pixel(t_game *game);
void	put_pixel_player(t_game *game, uint32_t x, uint32_t y, int color);
void	put_pixel_ray(t_game *game, int color);

// Raycasting
double	calculate_rayon_horizontal(t_game *game, int i);
double	calculate_rayon_vertical(t_game *game, int i);
int 	coll_ray(t_game *game, int i, int j);
void	find_shortest_ray(t_game *game, int i, double distH, double distV);
void    draw_column(t_game *game, int i, int test);
void	resize_hook(int width, int height, void *param);


#endif
