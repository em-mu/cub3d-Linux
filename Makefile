# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emuller <emuller@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/03 14:57:00 by emuller           #+#    #+#              #
#    Updated: 2023/07/06 14:52:04 by emuller          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = 	src/main.c \
		src/check_map.c \
		src/check_map2.c \
		src/get_next_line.c \
		src/get_next_line_utils.c \
		src/read_map.c \
		src/error.c \
		src/utils.c \
		src/parsing.c \
		src/parsing2.c \
		src/pixel.c \
		src/pixel2.c \
		src/hook.c \
		src/player.c \
		src/mouvement.c \
		src/mouvement2.c \
		src/raycasting.c \
		src/raycasting2.c \
		src/draw_column.c \
		src/draw_column2.c \


OBJS =		$(SRCS:.c=.o)

NAME = 		cub3d

CFLAGS = 	-Wall -Wextra -g3 -Werror

CC = 		gcc

INC	= 		-I /MLX42/include

MLX	= 		MLX42/libmlx42.a -L "/Users/$$USER/.brew/opt/glfw/lib"

LINUX = 	libmlx42.a -Iinclude -ldl -lglfw -pthread -lm

RM = 		rm -f

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		$(NAME)

$(NAME):	$(OBJS) libft.a
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ${LINUX} $(MLX) libft.a

debug:		$(OBJS) libft.a
			$(CC) $(CFLAGS) $(OBJS) ${LINUX} $(MLX) libft.a -fsanitize=address -o $(NAME)

libft.a :
			make -C libft
			mv ./libft/libft.a ./libft.a

clean:	
			$(RM) $(OBJS)
			make clean -C libft

fclean:		clean
			$(RM) $(NAME) 
			$(RM) libft.a
			make fclean -C libft

re: 		fclean all

.PHONY: 	all clean fclean re